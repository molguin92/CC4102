package cc4102.tarea3.olguin_romero;

/**
 * Created by arachnid92 on 08-12-15.
 */
public class VEBTree implements Tree {
    @Override
    public void put(int key, String value) {

    }

    @Override
    public String get(String key) {
        return null;
    }

    @Override
    public void delete(String key) {

    }

    @Override
    public int size() {
        return 0;
    }

    @Override
    public Node getRoot() {
        return null;
    }

    private class VEBNode extends Node
    {

        private int size;
        private VEBNode[] clusters;
        private VEBNode summary;
        private int max;
        private int min;

        public VEBNode(int size)
        {
            this.size = size;
            this.clusters = new VEBNode[(int) Math.sqrt(size)];
            this.max = -1;
            this.min = -1;
        }

        @Override
        Node put(int key, String value) {
            return null;
        }

        @Override
        String get(int key) {
            return null;
        }

        @Override
        Node delete(int key) {
            return null;
        }
    }
}
