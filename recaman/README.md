# Recamán to 3·10^7 (chat free turn, Oct 14 2026; graded in Code Oct 15)

a(0)=0; a(n)=a(n-1)-n if that is > 0 and unseen, else a(n-1)+n.

Files
- sealed.txt (sha256 e9a943bf9161e9cad6e68e9eb7bab765f83c45fc71e4d887fece83df939dd570): P1-P5, sealed before any computing.
- sealed2.txt (sha256 fa2cb358640ff7cd992001f4fed257832545ef1f7f80590ce9a2f3aeaa2b1581): P6-P8, sealed after the 10^7 outputs and before running further.
  Both were rebuilt here from the pasted text, and both hashes reproduce byte-exact.
- recaman.c: one pass, bitset of seen values (cap 1e9). `gcc -O3 -o recaman recaman.c && ./recaman 10000000`
- out_1e7.txt, out_3e7.txt: output, including 5·10^6 checkpoints and the raw window n=9960130..9960200.

Expected output (from chat): all reproduced.
- n <= 10^7: first repeat 42 at n=24; 19 first at n=99734; smallest missing 1355; max a(n) 61998984
  (at n=8466703); subtraction fraction 0.50000; adds - subs = 28; add-add pairs 5433, sub-sub 5406;
  a(10^7) = 20438710; missing values below 852655: 55772; latest value under 1000 to arrive: 879 at
  n=328002; steps with a(n) < n (n >= 2): 2878563.
- n <= 3·10^7: smallest missing 1355 at every 5·10^6 checkpoint; 852655 unseen; max a(n)/n for
  n > 100 is 7.382 at n=24399.
- Raw window: lanes near 10.48M (down by 1 per pair) and 20.44M (up by 1 per pair), the plunge to
  518390 at n=9960136, then a climb to 40358944 and the zig-zag between ~30.40M (descending) and
  ~40.36M (ascending). One detail differs: the climb from 518390 is four adds, not three
  (10478527, 20438665, 30398804, 40358944 at n=9960137..9960140).

Also at 3·10^7: max a(n) 178478968 at n=28758476; adds - subs = 30; add-add 8817, sub-sub 8787;
a(3·10^7) = 64321250; missing values below 852655 down to 25548; a(n) < n on 8896750 steps.

Open (from chat)
- Why the bottom lane skips holes like 852655.
- When 1355 is filled. Not by 3·10^7.
