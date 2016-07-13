#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/ec.h>
#include <openssl/ecdh.h>
/*NID_X9_62_prime256v1*/
#include <openssl/evp.h>

#include "cumino.h"

/*Nice little macro to save a few lines.*/
void die(const char *reason)
{
    fprintf(stderr, "%s\n", reason);
    fflush(stderr);
    exit(1);
}

/*Elliptic Curve Diffie-Hellman function*/
int EC_DH(unsigned char **secret, EC_KEY *key, const EC_POINT *pPub)
{
    int secretLen;

    secretLen = EC_GROUP_get_degree(EC_KEY_get0_group(key));
    secretLen = (secretLen + 7) / 8;

    *secret = (unsigned char*)malloc(secretLen);
    if (!(*secret))
        die("Failed to allocate memory for secret.\n");
    secretLen = ECDH_compute_key(*secret, secretLen, pPub, key, NULL);

    return secretLen;
}

/*Key generation function for throwaway keys.*/
EC_KEY* gen_key(void)
{
    EC_KEY *key;

    key = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
    if (key == NULL)
        die("Failed to create lKey object.\n");

    if (!EC_KEY_generate_key(key))
        die("Failed to generate EC key.\n");

    return key;
}

int main(int argc, char **argv)
{
    EC_KEY *lKey, *pKey;
    int lSecretLen, pSecretLen;
    unsigned char *lSecret, *pSecret;

    double t0,t1,t2,t3,t4,t5;

    t0 = now();
    lKey = gen_key();
    t1 = now();
    pKey = gen_key();
    t2 = now();
    print("gen_key: l:%f p:%f", t1-t0, t2-t1 );

    lSecretLen = EC_DH(&lSecret, lKey, EC_KEY_get0_public_key(pKey));
    t3 = now();
    pSecretLen = EC_DH(&pSecret, pKey, EC_KEY_get0_public_key(lKey));
    t4 = now();
    if (lSecretLen != pSecretLen) die("SecretLen mismatch.\n");
    if (memcmp(lSecret, pSecret, lSecretLen)) die("Secrets don't match.\n");
    print("EC_DH: l:%f p:%f", t3-t2, t4-t3);

    free(lSecret);
    free(pSecret);
    EC_KEY_free(lKey);
    EC_KEY_free(pKey);
    CRYPTO_cleanup_all_ex_data();
    t5 = now();
    print("clean: %f", t5-t4);
    return 0;
}
