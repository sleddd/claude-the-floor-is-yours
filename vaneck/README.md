# Van Eck sequence (chat, Oct 15 2026)

OEIS A181391: a(1)=0; a(n+1) = n - m, where m < n is the last index with a(m) = a(n), else 0.

Files
- predictions.txt: P1-P8 sealed before any computing, P9-P10 added after the 10^7 run and
  before the multi-scale run. `head -n 11 predictions.txt | sha256sum` gives
  0bf59b2a8b29445d62bdb8e3cb933d42cb82327ba0321ce9e359ead2cf9c12c9 (P1-P8);
  `sha256sum predictions.txt` gives 79c2bc3269e15c9c47bd1a233b61fa2f6f86f7d243c9787d425b89e8e25e9127.
  Both reproduce.
- ve2.c: zero count Z(N), Z·lnN/N and smallest unseen value at 1-2-5 steps to 10^8 (~400 MB).
  `gcc -O2 -o ve2 ve2.c -lm`. Output in ve2_out.txt.
- check.c: P1-P3 and the 10^7 statistics (mean, max, a(n)/n over n in [10^6, 10^7], deciles,
  distinct counts). Added in Code to redo chat's one-off script. Output in check_out.txt.

Expected output (from chat): all reproduced exactly.
- ve2: 10^3 198 1.3677 53; 10^4 1703 1.5685 251; 10^5 15099 1.7383 1594; 10^6 136529 1.8862 8756;
  10^7 1250523 2.0156 53791; 10^8 11576061 2.1324 295927.
- 10^7: mean a(n) 222552.2; max a(n) 9819448; max a(n)/n on [10^6, 10^7] 0.990816 at n=4516680;
  share with a(n)/n < 0.01 0.7697; deciles 0.8892 0.0358 0.0207 0.0146 0.0112 0.0090 0.0073 0.0060
  0.0045 0.0017; distinct values in the first 10^7 terms 1250522.
- Also checked: distinct values in the first 10^7 - 1 terms is 1250522 too, so Z(N) = 1 + D(N-1)
  at N = 10^7, as stated. No P2 violations for n < 10^7.

Open (from chat)
- Z·lnN/N is still rising at 10^8, with shrinking per-decade steps. Z·sqrt(lnN)/N is nearly flat
  (0.520 -> 0.497), but its fitted exponent creeps from 0.53 to 0.57. The true growth law of the
  zeros is unknown.
- Unexpected: late a(n)/n has density about 1/x from 0.1 to 0.7 (x · density ~ 0.05), sagging near 1.
  The deciles above agree: 0.0358 on [0.1, 0.2) gives 0.054 at x = 0.15; 0.0073 on [0.6, 0.7) gives 0.047.
