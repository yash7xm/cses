import java.util.Scanner;

public class EditDistance {
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        String s = in.nextLine();
        String p = in.nextLine();
        int m = s.length();
        int n = p.length();
        int[][] dp = new int[m+1][n+1];

        // base case when our s is empty we will return the lengtht of p simple at that point
        // (i==-1) return j+1
        // insertion kro
        for(int i=0; i<=n; i++){
            dp[0][i] = i;
        }

        // base case when our p is empty
        // (j==-1) return i+1
        // deletion kro
        for(int j=0; j<=m; j++){
            dp[j][0] = j;
        }

        // dp[i-1][j-1] for replace
        // dp[i-1][j] for deletion
        // dp[i][j-1] for insertion
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                if(s.charAt(i-1) == p.charAt(j-1)){
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    int max = Math.min(dp[i][j-1], dp[i-1][j]);
                    dp[i][j] = 1 + Math.min(dp[i-1][j-1], max);
                }
            }
        }

        System.out.println(dp[m][n]);
        in.close();
    }
}
