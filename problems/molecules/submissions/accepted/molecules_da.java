import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class molecules_da {

    private void work() {
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int n = sc.nextInt();
        int m = sc.nextInt();
        Map<Integer, Set<Integer>> g = new HashMap<>();
        int[] x = new int[n];
        int[] y = new int[n];
        boolean[] known = new boolean[n];
        for (int i = 0; i < n; i++) {
            x[i] = sc.nextInt();
            y[i] = sc.nextInt();
            if (x[i] >= 0) known[i] = true;
        }

        while (m-- > 0) {
            int u = sc.nextInt() - 1;
            int v = sc.nextInt() - 1;
            if (!g.containsKey(u)) g.put(u, new HashSet<>());
            if (!g.containsKey(v)) g.put(v, new HashSet<>());
            g.get(u).add(v);
            g.get(v).add(u);
        }
        sc.close();

        double[][] a = new double[2 * n][2 * n + 1];
        for (int i = 0; i < n; i++) {
            a[2 * i][2 * i] = a[2 * i + 1][2 * i + 1] = 1;
            if (known[i]) {
                a[2 * i][2 * n] = x[i];
                a[2 * i + 1][2 * n] = y[i];
            } else {
                int nn = g.get(i).size();
                for (int j : g.get(i)) {
                    a[2 * i][2 * j] = a[2 * i + 1][2 * j + 1] = -1.0 / nn;
                }
            }
        }

        for (int r = 0; r < 2 * n; r++) {
            int i = r;
            while (i < n && a[i][r] == 0) i++;

            double[] t = a[i];
            a[r] = a[i];
            a[i] = t;

            i = 2 * n;
            while (i >= r) a[r][i--] /= a[r][r];

            for (i = 0; i < 2 * n; i++) {
                if (i == r || a[i][r] == 0) continue;
                for (int j = 2 * n; j >= r; j--)
                    a[i][j] -= a[r][j] * a[i][r];
            }
        }

        for (int i = 0; i < n; i++) {
            System.out.printf("%.10f %.10f\n", a[2 * i][2 * n], a[2 * i + 1][2 * n]);
        }
    }

    public static void main(String[] args) {
        new molecules_da().work();
    }
}
