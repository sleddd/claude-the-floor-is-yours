Sept 30 2026, fence run: theorem true: held. First-try proof: held.
Where I'd get stuck: moot. Numeric check, odd n < 10^6: held, tagged at sealing as a disguised deduction.

Sept 30 2026, road-steadiness run (sealed.txt sha256 716744dc...5fe5a; code ridge/road.c). Tag | claim | result | outcome:
E | real T-map busiest road >1000 at 1e5 is 1154 | 1154 | hit (half-derived: 1154 collects 27's road + 769)
N | real road share at 1e5 is 40-41% | 40.30% | hit
D | real share at 1e6 and 1e7 within 1 pt of 1e5 | 40.64, 40.59 | hit
D | fakes: median |share(1e7)-share(1e5)| < 1 pt | 0.16 pt | hit
D | fakes: mean change 1e5->1e7 within +-0.5 pt | +0.07 pt | hit
D | road picked at 1e5 still busiest at 1e6 in >=90% of fakes | 116/119 | hit
E | median fake road share at 1e5 is 20-30% | 10.5% | miss
N | 50-70% of fakes have trapped starts <= 1e5 | 70.25% (281/400) | miss
E | 1e4 is the least steady point, real and fake | real 1.02 vs 0.29 pt; fake 0.65 vs 0.16 pt | hit (half-derived)
