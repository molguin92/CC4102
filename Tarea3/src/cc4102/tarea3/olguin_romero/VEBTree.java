package cc4102.tarea3.olguin_romero;

/**
 * Created by arachnid92 on 08-12-15.
 */
public class VEBTree implements Tree {

    int size;
    Node root;
    int max_size;

    public VEBTree(int max_size)
    {
        this.size = 0;
        this.root = null;
        this.max_size = max_size;
    }

    @Override
    public void put(int key, String value) {
        if (root == null)
            root = new VEBNode(this.max_size);
        root = root.put(key, value);
    }

    @Override
    public String get(int key)
    {
        if (root == null)
            return null;

        return root.get(key);
    }

    @Override
    public void delete(int key)
    {
        if (root == null)
            return;

        root = root.delete(key);
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public Node getRoot() {
        return root;
    }

    private class VEBNode extends Node
    {

        private int M;
        private VEBNode[] clusters;
        private VEBNode summary;
        private int max;
        private int min;
        private String max_value;

        public VEBNode(int size)
        {
            this.M = size;
            this.clusters = new VEBNode[(int) Math.sqrt(size)];
            this.max = -1;
            this.min = this.M;
        }

        @Override
        public Node put(int key, String value)
        {
            if (this.min > this.max) // we're empty
            {
                size++;
                this.max = key;
                this.min = key;
                this.max_value = value;
                this.value = value;
                return this;
            }

            if (this.summary == null)
                this.summary = new VEBNode((int) Math.sqrt(M));

            if ( key < this.min )
            {
                // swap min and key
                int temp = this.min;
                String tempv = this.value;

                this.min = key;
                this.value = value;

                key = temp;
                value = tempv;
            }
            else if (key > this.max)
            {
                this.max = key;
                this.max_value = value;
            }

            int i = (int) Math.floor(key/Math.sqrt(M));
            if (this.clusters[i] == null)
            {
                this.clusters[i] = new VEBNode((int) Math.sqrt(M));
                this.summary.put(i, null);
                size--;
            }
            this.clusters[i].put((int) (key%Math.sqrt(M)), value);
            return this;
        }

        @Override
        public String get(int key) {

            if( key == this.min ) // in this node
                return this.value;
            else if ( key == this.max ) // in this node
                return this.max_value;
            else if ( !( this.min < key && key < this.max ) ) return null; // out of range
            else
            {
                int i = (int) Math.floor(key / Math.sqrt(this.M));
                if (this.clusters[i] == null)
                    return null;
                else
                    return this.clusters[i].get((int) (key%Math.sqrt(M)));
            }
        }

        @Override
        public Node delete(int key) {
            if (this.max == key && this.min == key) // only one item, delete this node;
            {
                size--;
                return null;
            }
            else if ( this.summary == null )
            {
                if (this.min == key)
                    this.min = this.max;
                else if (this.max == key)
                    this.max = this.min;
                return this;
            }
            else if (this.min == key) // remove min and calculate a new minimum
            {
                int index = this.summary.min;
                this.min = this.clusters[index].min;
                this.value = this.clusters[index].value;
                this.clusters[index] = (VEBNode) this.clusters[index].delete((int) (this.min%Math.sqrt(M)));
                if (this.clusters[index] == null) {
                    this.summary = (VEBNode) this.summary.delete(index);
                    size++;
                }
            }
            else if (this.max == key) // remove max and calculate a new maximum
            {
                int index = this.summary.max;
                this.max = this.clusters[index].max;
                this.max_value = this.clusters[index].value;
                this.clusters[index] = (VEBNode) this.clusters[index].delete((int) (this.max%Math.sqrt(M)));
                if (this.clusters[index] == null) {
                    this.summary = (VEBNode) this.summary.delete(index);
                    size++;
                }
            }
            else if ( this.min < key && key < this.max )
            {
                int i = (int) Math.floor(key/Math.sqrt(M));
                this.clusters[i] = (VEBNode) this.clusters[i].delete((int) (key%Math.sqrt(M)));
                if (this.clusters[i] == null) {
                    this.summary = (VEBNode) this.summary.delete(i);
                    size++;
                }
            }

            return this;
        }
    }
}
