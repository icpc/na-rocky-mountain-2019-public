import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Scanner;

public class watchlater_da_tle {
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
        for(int i = 0; i < n; i++){
            if(map[list[i]] < 0) map[list[i]] = idx++;
            a[i] = map[list[i]];
        }

        memo = new int[1 << k];
        Arrays.fill(memo, -1);
        memo[(1 << k) - 1] = 0;

        System.out.println(go(0));
    }

    private int n, k, a[], memo[];

    private int go(int seen){
        if(memo[seen] >= 0) return memo[seen];
        int ret = Integer.MAX_VALUE;
        for(int i = 0; i < k; i++){
            if(((1<< i) & seen) == 0){
                int clicks = 0;
                boolean yeah = false;
                for(int vid = 0; vid < n; vid++){
                    int j = a[vid];
                    if(j == i){
                        if(!yeah){
                            yeah = true;
                            clicks++;
                        }
                    }else{
                        if(((1 << j) & seen) == 0){
                            yeah = false;
                        }
                    }
                }
                int t = clicks + go(seen | (1 << i));
                if(t < ret) ret = t;
            }
        }
        return memo[seen] = ret;
    }

    public static void main(String[] args) {
        new watchlater_da_tle().work();
    }
}
