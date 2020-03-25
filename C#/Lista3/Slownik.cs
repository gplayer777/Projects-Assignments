using System;


namespace NowyProjekt
{

    public class Slowo<K, V>
    {

        public K key;
        public V value;
        public Slowo<K, V> next;
        public Slowo<K, V> prev;
   
    }

    public class Slownik<K, V>
    {

        protected Slowo<K, V> header;
        protected Slowo<K, V> last;


        public void add(K key, V value)
        {

            Slowo<K, V> n = new Slowo<K, V>
            {
                value = value,
                key = key,
                next = null,
                prev = null
            };

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

        public bool find(K key)
        {

            Slowo<K, V> s = new Slowo<K, V>();
            s = header;



            while (s != null)
            {
                if (s.key.Equals(key))
                    return true;

                s = s.next;
            }


            return false;
        }

        public void print()
        {

            Slowo<K, V> s = new Slowo<K, V>();
            s = header;
            if (s == null)
                Console.WriteLine("nic nie ma");


            while (s != null)
            {
                Console.WriteLine(s.value);

                s = s.next;
            }


        
        }

        public void remove(K key)
        {

            Slowo<K, V> s = new Slowo<K, V>();
            s = header;

            if (!s.key.Equals(key))
            {

                while (s != null)
                {

                    s = s.next;

                    if (s.key.Equals(key))
                        break;


                }
            }



            if (s.key.Equals(key))
            {

                if (last == header)
                {
                    last = null;
                    header = null;
                }

                else if (s == header)
                {
                    header.next.prev = null;
                    header = header.next;
                }

                else if (s == last)
                {

                    last.prev.next = null;
                    last = last.prev;

                }

                else if(s != last && s!= header)
                {
                    s.prev.next = s.next;
                    s.next.prev = s.prev;
                    s = null;

                }
           }




        }

    


}

class Program
{
        static void Main(string[] args)
        {


        Slownik<int, string> s = new Slownik<int, string>();
            s.add(1, "kacper");
            s.add(2, "gosia");

            Console.WriteLine(s.find(1));
            s.print();
            s.remove(1);
            s.find(1);
            s.remove(2);
            s.print();


        }
    }
}
