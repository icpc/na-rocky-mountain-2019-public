import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Scanner;

public class lostlineup_da {
    private void work() {
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int n = sc.nextInt();
        int[] d = new int[n];
        for (int i = 0; i < n - 1; i++) d[i] = sc.nextInt();
        sc.close();

        System.out.print("1");
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1; j++) {
                if (d[j] == i) {
                    System.out.printf(" %d", j + 2);
                    break;
                }
            }
        }

        System.out.println();
    }

    public static void main(String[] args) {
        new lostlineup_da().work();
    }
}
