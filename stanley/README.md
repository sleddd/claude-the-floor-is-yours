# Stanley sequence S(0,4) (chat, Oct 27 2026)

Greedy 3-AP-free sequence: a(1)=0, a(2)=4, then each term is the smallest value above the
last that makes no 3-term arithmetic progression with two earlier terms.

Files
- sealed.txt (sha256 2fa7c34cd36a5277ad800954302926990ff8d5e8bc6cb1603773dc4b555b5853): P1-P3.
- sealed2.txt (sha256 25bfa4b9cf5a032002593be264c7258a43e2407f24aae32f7eb1d8457604d84a): P4-P6.
- sealed3.txt (sha256 ee579a90eceb1c283a5993539d101fa955284eae1ebda520c161cef1b8c91a0a): P7-P9, turn 2.
  All three were rebuilt here from the pasted text (each ending in a newline), and all three hashes
  reproduce byte-exact.
- stanley.c: bitset of forbidden values; on adding x, mark 2x - a[i] for every earlier a[i],
  skipping marks >= MAXV by binary search. `gcc -O3 -o stanley stanley.c && ./stanley 0 4 120000 > big.txt`
  (~24 s here, 125 MB bitset). big.txt is not committed.
- analyze.py: sprint detector (start where a(n+30)/a(n) > 1.08, extend while > 1.02, search from
  n = 1000 unless given), ratios, a·ln n/n², a/n², exponents. Output in analyze_out.txt.
- bands.py: 1.06x density bins, pair census (150 skipped t in [150M, 175M), random.seed(1)) and
  pressure scan (60 non-members per 6M bin, random.seed(2)). Output in bands_out.txt.
- density.py: mean and peak density of each cycle's dense band, for P9. Output in density_out.txt.

Indexing: n is 1-indexed (a(1) = 0). Chat's a(40000) and a(120000) use that; chat's sprint list is
0-indexed (a(1958) there is a(1959) here). Values agree either way.

Expected output (from chat)
- a(40000) = 52781167, a(120000) = 522014588, S(0,1) a(40000) = 15116908, first 24 terms: all exact.
- Sprint starts, values, index ratios and value ratios: all exact, with n shifted by one as above.
  The detector also fires at n = 1114 (76584) when it searches from 1000; chat's list starts at
  1958, which is what a search from 1500 gives.
- a·ln n/n² at the sprint starts, 0.4440 -> 0.3589: exact.
- Band picture (dense 74-112M, thin 112-150M, near-empty 149-178M, dense again from ~188M): agrees.
- Pressure scan: every bin exact.
- Pair census: reps min 5 / median 15 / max 27, a in <7M 0.396 and 29-44M 0.280 exact. Two differ:
  a in 11-18M is 0.248 (chat 0.255), and b in the 74-112M band is 0.982 (chat ~95%).

Also: per-cycle density of the dense band falls by 1.45-1.59x (mean) and 1.37-1.65x (peak); the
mean ratio rises cycle by cycle (1.452 ... 1.589), as value ratio / index ratio would give with the
index ratio drifting down.

Open (from chat)
- Why the excess over 2 in the value ratio is ~1.25 and whether it shrinks (index-ratio drift:
  1.660 -> 1.639 so far).
- Whether the index ratio drifts to 1 or to a limit; the true log power.
