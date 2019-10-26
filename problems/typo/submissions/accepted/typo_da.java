import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.*;

public class typo_da {

    private static final long MOD = 1999999973L;
    private static final long P1 = 17L;
    private static final long P1_INV = 470588229L;
    private static final long P2 = 23L;
    private static final long P2_INV = 608695644L;

    private void work() {
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int n = sc.nextInt();
        long[] h1 = new long[n];
        long[] h2 = new long[n];
        Map<Long, Set<Integer>> hMap1 = new HashMap<>();
        Map<Long, Set<Integer>> hMap2 = new HashMap<>();
        char[][] ss = new char[n][];

        for (int i = 0; i < n; i++) {
            ss[i] = sc.next().toCharArray();
            h1[i] = getHash(ss[i], P1);
            if (!hMap1.containsKey(h1[i])) hMap1.put(h1[i], new HashSet<>());
            hMap1.get(h1[i]).add(i);
            h2[i] = getHash(ss[i], P2);
            if (!hMap2.containsKey(h2[i])) hMap2.put(h2[i], new HashSet<>());
            hMap2.get(h2[i]).add(i);
        }

        sc.close();

        boolean found = false;
        for (int i = 0; i < n; i++) {
            if (ss[i].length == 1) continue;

            long tail1 = 0;
            long powp1 = powMod(P1, ss[i].length - 1);
            long tail2 = 0;
            long powp2 = powMod(P2, ss[i].length - 1);
            for (int j = 0; j < ss[i].length; j++) {
                long newTail1 = (tail1 + powp1 * ss[i][j]) % MOD;
                long candidate1 = (h1[i] - newTail1 + MOD + tail1 * P1_INV) % MOD;
                long newTail2 = (tail2 + powp2 * ss[i][j]) % MOD;
                long candidate2 = (h2[i] - newTail2 + MOD + tail2 * P2_INV) % MOD;
                if (hMap1.containsKey(candidate1) && hMap2.containsKey(candidate2)) {
                    Set<Integer> set = new HashSet<>(hMap1.get(candidate1));
                    set.retainAll(hMap2.get(candidate2));
                    if (!set.isEmpty()) {
                        found = true;
                        System.out.println(new String(ss[i]));
                        break;
                    }
                }

                tail1 = newTail1;
                powp1 = (powp1 * P1_INV) % MOD;
                tail2 = newTail2;
                powp2 = (powp2 * P2_INV) % MOD;
            }
        }

        if (!found) {
            System.out.println("NO TYPOS");
        }
    }


    private long getHash(char[] s, long p) {
        long hash = 0;
        for (char c : s) {
            hash = ((p * hash) + c) % MOD;
        }

        return hash;
    }

    private long powMod(long n, int k) {
        if (k == 0) return 1L;
        if ((k & 1) != 0) return (n * powMod(n, k - 1)) % MOD;
        long t = powMod(n, k / 2);
        return (t * t) % MOD;
    }

    private void printPrimes() {
        BigInteger pp = BigInteger.valueOf(2000000000L);
        while (!pp.isProbablePrime(10)) {
            pp = pp.subtract(BigInteger.ONE);
        }

        System.out.printf("private static final long MOD = %dL;\n", pp);
        System.out.printf("private static final long P1 = %dL;\n", P1);
        System.out.printf("private static final long P1_INV = %dL;\n", BigInteger.valueOf(P1).modInverse(pp));
        System.out.printf("private static final long P2 = %dL;\n", P2);
        System.out.printf("private static final long P2_INV = %dL;\n", BigInteger.valueOf(P2).modInverse(pp));
    }

    public static void main(String[] args) {
        // new typo_da().printPrimes();
        new typo_da().work();
    }
}
