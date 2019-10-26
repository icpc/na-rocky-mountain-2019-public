import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Scanner;

public class tiredterry_da {
    private void work() {
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int n = sc.nextInt();
        int w = sc.nextInt();
        int d = sc.nextInt();
        String s = sc.next();
        sc.close();

        char[] a = (s + s).toCharArray();
        int ans = 0;
        int left = 0;
        int cur = a[0] == 'Z' ? 1 : 0;
        for (int i = 1; i < 2 * n; i++) {
            cur += a[i] == 'Z' ? 1 : 0;
            if (i - left == w) cur -= a[left++] == 'Z' ? 1 : 0;
            if (i >= n) ans += cur < d ? 1 : 0;
        }

        System.out.println(ans);
    }

    public static void main(String[] args) {
        new tiredterry_da().work();
    }
}
