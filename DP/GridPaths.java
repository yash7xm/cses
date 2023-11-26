import java.util.Scanner;

public class GridPaths {
    public static final int MOD = 1000000007;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        in.nextLine();
        int[][] a = new int[n][n];
        for (int i = 0; i < n; i++) {
            String s = in.nextLine();
            for (int j = 0; j < n; j++) {
                if (s.charAt(j) == '.') a[i][j] = 1;
                else a[i][j] = 0;
            }
        }
        int[][] dp = new int[n][n];
        boolean flag = false;

        for (int i = 0; i < n; i++) {
            if (a[0][i] == 0) flag = true;
            if (flag) dp[0][i] = 0;
            else dp[0][i] = a[0][i];
        }
        flag = false;

        for (int i = 0; i < n; i++) {
            if (a[i][0] == 0) flag = true;
            if (flag) dp[i][0] = 0;
            else dp[i][0] = a[i][0];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (a[i][j] == 0) dp[i][j] = 0;
                else dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
            }
        }

        System.out.println(dp[n - 1][n - 1]);
        in.close();
    }
}
