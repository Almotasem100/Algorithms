import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;

public class PercolationStats {
    private static final double CONF_95 = 1.96;
    private final double[] results;


    // perform independent trials on an n-by-n grid
    public PercolationStats(int n, int trials) {
        if (n <= 0 || trials <= 0) {
            throw new IllegalArgumentException("Argument is outside its prescribed range");
        } else {
            this.results = new double[trials];
            for (int i = 0; i < trials; i++) {
                Percolation pc = new Percolation(n);
                while (!pc.percolates()) {
                    int row = StdRandom.uniform(1, n + 1);
                    int col = StdRandom.uniform(1, n + 1);
                    pc.open(row, col);
                }
                this.results[i] = (double) pc.numberOfOpenSites() / (n * n);
            }
        }
    }

    // sample mean of percolation threshold
    public double mean() {
        return StdStats.mean(this.results);
    }

    // sample standard deviation of percolation threshold
    public double stddev() {
        return StdStats.stddev(this.results);
    }

    // low endpoint of 95% confidence interval
    public double confidenceLo() {
        double m = mean();
        double s = stddev();
        return m - ((CONF_95 * s) / Math.sqrt(this.results.length));
    }

    // high endpoint of 95% confidence interval
    public double confidenceHi() {
        double m = mean();
        double s = stddev();
        return m + ((CONF_95 * s) / Math.sqrt(this.results.length));
    }

    // test client (see below)
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        int t = Integer.parseInt(args[1]);
        PercolationStats pcs = new PercolationStats(n, t);
        StdOut.println("mean = " + pcs.mean());
        StdOut.println("stddev = " + pcs.stddev());
        StdOut.println("95% confidence interval = [" + pcs.confidenceLo() +
                ", " + pcs.confidenceHi() + "]");
    }
}
