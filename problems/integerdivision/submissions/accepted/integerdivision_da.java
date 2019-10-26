import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class integerdivision_da {

    private void work() {
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        Map<Integer, Long> m = new HashMap<>();
        int n = sc.nextInt();
        int d = sc.nextInt();
        while (n-- > 0) {
            int a = sc.nextInt() / d;
            if (!m.containsKey(a)) m.put(a, 0L);
            m.put(a, m.get(a) + 1);
        }
        sc.close();

        long res = 0;
        for (Map.Entry<Integer, Long> e : m.entrySet()) {
            long x = e.getValue();
            if (x > 1) {
                res += x * (x - 1) / 2;
            }
        }

        System.out.println(res);
    }

    public static void main(String[] args) {
        new integerdivision_da().work();
    }
}
