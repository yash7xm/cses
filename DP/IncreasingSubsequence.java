import java.util.Scanner;

public class IncreasingSubsequence {
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[] a = new int[n];
        for(int i=0; i<n; i++){
            a[i] = in.nextInt();
        }

        int[] dp = new int[n];
        dp[0] = 1;
        int ans = 0;
        for(int i=1; i<n; i++){
            for(int j=i-1; j>=0; j--){
                if(a[j] < a[i]){
                    dp[i] = Math.max(dp[j], dp[i]);
                }
            }
            dp[i]++;
            ans = Math.max(ans, dp[i]);
        }

        System.out.println(ans);
        in.close();
    }
}
