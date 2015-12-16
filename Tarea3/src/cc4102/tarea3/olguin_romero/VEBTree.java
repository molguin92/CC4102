package cc4102.tarea3.olguin_romero;

public class VEBTree {

    private VEBNode root;
    private static int MIN_SIZE = 2;

    public VEBTree(int size) {
        root = new VEBNode(size);
    }

    public void put(int x) {
        root.put(x);
    }

    public boolean contains(int x) {
        return root.contains(x);
    }

    public void delete(int x) {
        root.delete(x);
    }

    protected class VEBNode {

        int size;
        int sqrt;
        int max;
        int min;
        VEBNode[] clusters;
        VEBNode summary;

        public VEBNode(int size) {
            this.size = size;
            this.max = -1;
            this.min = size;
            this.sqrt = this.higherSquareRoot();
            clusters = new VEBNode[sqrt];
            summary = null;
        }

        public void put(int x) {
            if(this.isEmpty())
            {
                this.min = x;
                this.max = x;
                return;
            }

            if(x < this.min)
            {
                int temp = x;
                x = this.min;
                this.min = temp;
            }

            if(x > this.max)
                this.max = x;

            if(x > this.min && this.size > VEBTree.MIN_SIZE)
            {
                int hi = this.high(x);
                int li = this.low(x);

                if(this.clusters[hi] == null)
                {
                    this.clusters[hi] = new VEBNode(sqrt);
                    if(this.summary == null)
                        this.summary = new VEBNode(sqrt);
                    this.summary.put(hi);
                }

                this.clusters[hi].put(li);
            }
        }

        public boolean contains(int x) {
            if(x == this.min || x == this.max)
                return true;
            else if (this.size == VEBTree.MIN_SIZE)
                return false;
            else
            {
                int hi = this.high(x);
                int li = this.low(x);

                if(this.clusters[hi] == null)
                    return false;
                else
                    return this.clusters[hi].contains(li);
            }
        }

        void delete(int x) {
            if(this.min == this.max)
            {
                this.min = this.size;
                this.max = -1;
            }
            else if(VEBTree.MIN_SIZE == this.size)
            {
                if(0 == x)
                {
                    this.min = 1;
                }
                else
                {
                    this.min = 0;
                }
                this.max = this.min;
            }
            else if(x == this.min)
            {
                int summaryMin = this.summary.min;
                x = (int) (summaryMin * lowerSquareRoot() + this.clusters[summaryMin].min);
                this.min = x;

                int highOfX = high( x);
                int lowOfX = low(x);
                this.clusters[highOfX].delete(lowOfX);

                if(this.clusters[highOfX].size == this.clusters[highOfX].min)
                {
                    this.summary.delete(highOfX);
                    if(x == this.max)
                    {
                        int summaryMax = this.summary.max;
                        if(-1 == summaryMax)
                        {
                            this.max = this.min;
                        }
                        else
                        {
                            this.max = (int) (summaryMax * lowerSquareRoot() + this.clusters[summaryMax].max);
                        }
                    }
                }
                else if(x == this.max)
                {
                    this.max = (int) (highOfX * lowerSquareRoot() +  this.clusters[highOfX].max);
                }
            }
        }

        boolean isEmpty() {
            return this.max < this.min;
        }

        /*
	    * Returns the integer value of the first half of the bits of x.
	    */
        private int high(int x)
        {
            return (int)Math.floor(x / this.lowerSquareRoot());
        }


        /*
         * Returns the integer value of the second half of the bits of x.
         */
        private int low(int x)
        {
            return x % (int)this.lowerSquareRoot();
        }


        /*
         * Returns the value of the least significant bits of x.
         */
        private double lowerSquareRoot()
        {
            return Math.pow(2, Math.floor((Math.log10(this.size) / Math.log10(2)) / 2.0));
        }

        private int higherSquareRoot()
        {
            return (int)Math.pow(2, Math.ceil((Math.log10(this.size) / Math.log10(2)) / 2.0));
        }
    }
}
