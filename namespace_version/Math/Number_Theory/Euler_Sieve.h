

const int N = 1e7 + 10;
const int PrimeNum = 1e6 + 10;

namespace Euler_Sieve {
    /*
    require:
        constant: N PrimeNum
    */

    void prime (bool isntPrime[N], int prime[PrimeNum], int & tot, int n) {
        isntPrime[1] = true;

        tot = 0;
        for (int i = 2; i <= n; i++) {
            if (!isntPrime[i]) {
                tot++;
                prime[tot] = i;
            }

            for (int j = 1; (j <= tot) && (i * prime[j] <= n); j++) {
                isntPrime[i * prime[j]] = true;

                if (i % prime[j] == 0) {
                    break;
                }
            }
        }
    }

    void prime_and_phi (bool isntPrime[N], int prime[PrimeNum], int & tot, int phi[N], int n) {
        isntPrime[1] = true;
        phi[1] = 1;

        tot = 0;
        for (int i = 2; i <= n; i++) {
            if (!isntPrime[i]) {
                tot++;
                prime[tot] = i;
                phi[i] = i - 1;
            }

            for (int j = 1; (j <= tot) && (i * prime[j] <= n); j++) {
                isntPrime[i * prime[j]] = true;

                if (i % prime[j] == 0) {
                    phi[i * prime[j]] = phi[i] * prime[j];
                    break;
                }
                phi[i * prime[j]] = phi[i] * phi[prime[j]];
            }
        }
    }

    void prime_and_mu (bool isntPrime[N], int prime[PrimeNum], int & tot, int mu[N], int n) {
        isntPrime[1] = true;
        mu[1] = 1;

        tot = 0;
        for (int i = 2; i <= n; i++) {
            if (!isntPrime[i]) {
                tot++;
                prime[tot] = i;
                mu[i] = -1;
            }

            for (int j = 1; (j <= tot) && (i * prime[j] <= n); j++) {
                isntPrime[i * prime[j]] = true;

                if (i % prime[j] == 0) {
                    break;
                }
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
}