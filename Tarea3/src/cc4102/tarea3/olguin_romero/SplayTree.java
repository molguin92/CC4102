package cc4102.tarea3.olguin_romero;

import sun.reflect.generics.reflectiveObjects.NotImplementedException;

/**
 * Created by arachnid92 on 07-12-15.
 */
public class SplayTree implements Tree {

    int size;
    SplayNode root;

    public SplayTree()
    {
        this.size = 0;
        this.root = null;
    }

    @Override
    public void put(int key, String value) {
        if(root == null) {
            size++;
            root = new SplayNode(key, value, null);
        }
        else
            root = (SplayNode) root.put(key, value);
    }

    @Override
    public String get(int key) {
        if(root == null)
            return null;
        else {
            root = (SplayNode) root.splay(key);
            if (root.key != key)
                return null;
            else return root.value;
        }
    }

    @Override
    public void delete(int key) {
        if (root != null) {
            root = (SplayNode) root.splay(key);
            if (root.key == key) {
                // split, pop and join
                SplayNode left = (SplayNode) root.left;
                SplayNode right = (SplayNode) root.right;

                if(left == null && right == null)
                {
                    root = null;
                }
                else if (left == null)
                {
                    root = right;
                    right.parent = null;
                }
                else if (right == null)
                {
                    root = left;
                    left.parent = null;
                }
                else
                {
                    // find largest item in left
                    while(left.right != null)
                        left = (SplayNode) left.right;

                    root = (SplayNode) left.splay(key);
                    root.right = right;
                    right.parent = root;
                }
            }
        }
    }

    @Override
    public int size() {
        return this.size;
    }

    @Override
    public Node getRoot() {
        return root;
    }


    protected class SplayNode extends Node
    {
        SplayNode parent;

        SplayNode(int key, String value, SplayNode parent)
        {
            this.key = key;
            this.value = value;
            this.parent = parent;
        }

        @Override
        public Node put(int key, String value)
        {
            if(this.key == key)
            {
                // found correct node
                this.value = value;
                return this.splay(key);
            }
            else if (key < this.key)
            {
                // put left
                if(this.left == null)
                {
                    size++;
                    this.left = new SplayNode(key, value, this);
                    return ((SplayNode)this.left).splay(key);
                }
                else
                    return this.left.put(key, value);
            }
            else
            {
                // put right
                if(this.right == null)
                {
                    size++;
                    this.right = new SplayNode(key, value, this);
                    return ((SplayNode)this.right).splay(key);
                }
                else
                    return this.right.put(key, value);
            }
        }

        @Override
        public String get(int key) {
            throw new NotImplementedException();
        }

        @Override
        public Node delete(int key) {
            throw new NotImplementedException();
        }

        private void rotateRight()
        {
            /*
            we are the left child of parent, and we rotate to be the parent of our parent
             */
            SplayNode p = this.parent;
            this.parent = p.parent;
            p.parent = this;

            if(this.right != null)
                ((SplayNode)this.right).parent = p;
            p.left = this.right;
            this.right = p;
        }

        private void rotateLeft()
        {
            /*
            we are the right child of parent, and we rotate to be the parent of our parent
             */
            SplayNode p = this.parent;
            this.parent = p.parent;
            p.parent = this;

            if(this.left != null)
                ((SplayNode)this.left).parent = p;
            p.right = this.left;
            this.left = p;
        }

        public Node splay(int key)
        {
            if (this.key == key || (this.key < key && this.left == null) || (this.key > key && this.right == null))
            {
                // either we found the key, or it's not in the tree and we're at the closest node
                // either way, we splay from here up!

                if (this.parent == null) // we are at the root, no need to do anything
                    return this;
                else if (this.parent.parent == null) // parent is the root
                {
                    if (key < this.parent.key) // left case - zig
                    {
                        this.rotateRight();
                        return this;
                    }
                    else // right case - zag
                    {
                        this.rotateLeft();
                        return this;
                    }
                }
                else
                {
                    // zig-zig, zig-zag, zag-zig or zag-zag
                    if(key < this.parent.key) // *-zig
                    {
                        if(key < this.parent.parent.key) // zig-zig, left-left
                        {
                            this.parent.rotateRight();
                            this.rotateRight();
                            return this.splay(key);
                        }
                        else // zag-zig, right-left
                        {
                            this.rotateRight();
                            this.rotateLeft();
                            return this.splay(key);
                        }
                    }
                    else // *-zag
                    {
                        if(key < this.parent.parent.key) // zig-zag, left-right
                        {
                            this.rotateLeft();
                            this.rotateRight();
                            return this.splay(key);
                        }
                        else // zag-zag, right-right
                        {
                            this.parent.rotateLeft();
                            this.rotateLeft();
                            return this.splay(key);
                        }
                    }
                }
            }
            else // keep searching
            {
                if(key < this.key)
                    return ((SplayNode)this.left).splay(key);
                else
                    return ((SplayNode)this.right).splay(key);
            }
        }
    }
}
