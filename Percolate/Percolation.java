import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
    // creates n-by-n grid, with all sites initially blocked
    private static final byte OPEN_SITE = 100;
    private static final byte UP_SITE = 101;
    private static final byte DOWN_SITE = 110;
    private final int gridLength;
    private final byte[] status;
    private final WeightedQuickUnionUF wuf;
    private int countOpen = 0;
    private boolean percolationFlag = false;


    public Percolation(int n) {
        if (n <= 0) {
            throw new IllegalArgumentException("Argument is outside its prescribed range");
        } else {
            this.gridLength = n;
            this.wuf = new WeightedQuickUnionUF(n * n + 1);
            this.status = new byte[n * n + 1];
        }
    }

    public void open(int row, int col) {
        if (row > gridLength || col > gridLength) {
            throw new IllegalArgumentException("Argument is outside its prescribed range");
        } else if (row <= 0 || col <= 0) {
            throw new IllegalArgumentException("Argument is outside its prescribed range");
        } else if (isOpen(row, col)) {
            return;
        }
        countOpen++;
        int myCell = getCell(row, col);
        this.status[myCell] = OPEN_SITE;
        byte result = this.status[wuf.find(myCell)];
        if (row - 1 > 0) {
            if (isOpen(row - 1, col)) {
                int upCell = getCell(row - 1, col);
                result |= this.status[wuf.find(upCell)];
                wuf.union(myCell, upCell);
            }
        } else {
            result |= UP_SITE;
        }
        if (row + 1 <= this.gridLength) {
            if (isOpen(row + 1, col)) {
                int downCell = getCell(row + 1, col);
                result |= this.status[wuf.find(downCell)];
                wuf.union(myCell, downCell);
            }
        } else {
            result |= DOWN_SITE;
        }
        if (col + 1 <= this.gridLength && isOpen(row, col + 1)) {
            int rightCell = getCell(row, col + 1);
            result |= this.status[wuf.find(rightCell)];
            wuf.union(myCell, rightCell);

        }
        if (col - 1 > 0 && isOpen(row, col - 1)) {
            int leftCell = getCell(row, col - 1);
            result |= this.status[wuf.find(leftCell)];
            wuf.union(myCell, leftCell);

        }
        this.status[wuf.find(myCell)] = result;
        if (this.status[wuf.find(myCell)] == 111) {
            percolationFlag = true;
        }
    }

    // is the site (row, col) open?
    public boolean isOpen(int row, int col) {
        if (row > gridLength || col > gridLength) {
            throw new IllegalArgumentException("Argument is outside its prescribed range");
        } else if (row <= 0 || col <= 0) {
            throw new IllegalArgumentException("Argument is outside its prescribed range");
        } else {
            return ((this.status[getCell(row, col)] & OPEN_SITE) == OPEN_SITE);
        }
    }

    // is the site (row, col) full?
    public boolean isFull(int row, int col) {
        if (row > gridLength || col > gridLength) {
            throw new IllegalArgumentException("Argument is outside its prescribed range");
        } else if (row <= 0 || col <= 0) {
            throw new IllegalArgumentException("Argument is outside its prescribed range");
        } else {
            if (isOpen(row, col)) {
                int myCell = getCell(row, col);
                return (this.status[wuf.find(myCell)] & UP_SITE) == UP_SITE;
            }
            return false;
        }
    }

    private int getCell(int row, int col) {
        return (row - 1) * this.gridLength + col;

    }

    // returns the number of open sites
    public int numberOfOpenSites() {
        return countOpen;
    }

    // does the system percolate?
    public boolean percolates() {
        return percolationFlag;
    }

    // test client (optional)
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        Percolation pc = new Percolation(n);
        StdOut.println("open: " + pc.isOpen(1, 17));
        pc.open(1, 17);
        StdOut.println("open: " + pc.isOpen(1, 17));
        StdOut.println("full: " + pc.isFull(1, 17));
        StdOut.println("hi: " + pc.percolates());
        StdOut.println("no: " + pc.numberOfOpenSites());
    }
}
