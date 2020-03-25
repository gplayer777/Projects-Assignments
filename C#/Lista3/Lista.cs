using System;

namespace Biblioteka
{
    public class Node<T>
    {
        public T val;
        public Node<T> next;
        public Node<T> prev;

    }


    public class Lista<T>//:List
    {

        protected Node<T> header;
        protected Node<T> last;




        public void addFirst(T value)
        {
            Node<T> n = new Node<T>();
            n.val = value;

            n.prev = null;

            if (last == null)
            {
                header = n;
                last = n;
            }
            else
            {
                n.next = header;
                header.prev = n;
                header = n;
            }

        }

        public void addLast(T value)
        {
            Node<T> n = new Node<T>();
            n.val = value;
            n.next = null;
            if (last == null)
            {
                header = n;
                last = n;
            }

            else
            {
                n.prev = last;
                last.next = n;
                last = n;
            }


        }

        public void PrintList()
        {
            Node<T> n = new Node<T>();
            n = header;

            while (n != null)
            {
                Console.WriteLine(n.val);
                n = n.next;

            }


        }

        public Boolean isEmpty()
        {
            if (last == null)
                return true;
            else
                return false;
        }

        public void removeLast()
        {

            if (last == header)
            {
                last = null;
                header = null;
            }
            else
            {
                last.prev.next = null;
                last = last.prev;


            }


        }
        public void removeFirst()
        {

            if (last == header)
            {
                last = null;
                header = null;
            }
            else
            {
                header.next.prev = null;
                header = header.next;



            }

        }










    }

}
