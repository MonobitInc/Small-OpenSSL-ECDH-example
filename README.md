# Small-OpenSSL-ECDH-example
An atomized example of Elliptic Curve Diffie-Hellman using OpenSSL


ECDHの鍵交換のローカル側(l)とピア側(p)を両方1個のプログラム内で行い、
OpenSSLの関数の所要時間を計測する。

ループ1回めについては、鍵が正常に作られているかどうかをダンプしている。

以下の出力例では、gen_keyが片側1msていど、 EC_DHも大体1ms程度で完了している。(Core i7 2.3GHz)

したがってシングルスレッドプロセスでも、毎秒数百コネクションまでなら何とか耐え切れる計算となる。


<pre>
gen_key time: l:0.000956 p:0.000799
lKey priv:7DB1DC6511FC860D95BCA97E0A70BFD0BE51884A1EFD537BCD50C820C57531F9 pub:0439E51E64B85A6C518616C1216448014CCB4A058AABE921CDE5774559AAB50AF435607F3B9E0398E3ECECE3A563BD4537DA77E6892CDFE8F0F0E4FC1B3E6B0128
pKey priv:200A50ED66790192BF02EECABFCDDB6DD951B3EC84915C0170A7581BB74EDC49 pub:043675A0E87774700A7ADA7ACD3A2D752130EC4B95BACBF4B9EA0F716DD4F5068E7B3F1A4DDA4B44479406554BC86DE7B56B6186AE5980D8708BC549B6AF034916
EC_DH time: l:0.000990 p:0.000738
lSecret: len:32 dump:
56 20 2a 2d 22 88 99 4a   d6 15 e0 1b 57 9e db 52   
34 79 5f 6f 9c b5 a8 32   55 4c f4 0a ea f5 86 9a   

pSecret: len:32 dump:
56 20 2a 2d 22 88 99 4a   d6 15 e0 1b 57 9e db 52   
34 79 5f 6f 9c b5 a8 32   55 4c f4 0a ea f5 86 9a   

clean time: 0.000155
gen_key time: l:0.000859 p:0.000721
EC_DH time: l:0.000777 p:0.001298
clean time: 0.000021
gen_key time: l:0.000680 p:0.000680
EC_DH time: l:0.000703 p:0.000684
clean time: 0.000010
gen_key time: l:0.000706 p:0.000678
EC_DH time: l:0.000722 p:0.000747
clean time: 0.000010
gen_key time: l:0.000708 p:0.000692
EC_DH time: l:0.000700 p:0.000696
clean time: 0.000008
</pre>