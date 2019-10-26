import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Scanner;

public class watchlater_da {
    private void work() {
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        n = sc.nextInt();
        k = sc.nextInt();
        char[] list = sc.next().toCharArray();
        sc.close();

        int[] map = new int[256];
        Arrays.fill(map, -1);
        int idx = 0;
        a = new int[n];
        for (int i = 0; i < n; i++) {
            if (map[list[i]] < 0) map[list[i]] = idx++;
            a[i] = map[list[i]];
        }

        memo = new int[1 << k];
        Arrays.fill(memo, -1);
        memo[(1 << k) - 1] = 0;


        System.out.println(go(0));
    }

    private int n, k, a[], memo[];

    private int go(int seen) {
        if (memo[seen] >= 0) return memo[seen];
        int[] clicks = new int[k];
        int last = -1;
        for (int i = 0; i < n; i++) {
            int j = a[i];
            if (((1 << j) & seen) == 0) {
                if (j != last) {
                    last = j;
                    clicks[j]++;
                }
            }
        }

        int ret = Integer.MAX_VALUE;
        for (int i = 0; i < k; i++) {
            if (clicks[i] > 0) {
                int t = clicks[i] + go(seen | (1 << i));
                if (t < ret) ret = t;
            }
        }
        return memo[seen] = ret;
    }

    private static void print(String s, int[] x){
        System.out.print(s);
        for(int i : x) System.out.printf(" %d", i);
        System.out.println();
    }

    public static void main(String[] args) {
        new watchlater_da().work();
    }
}
