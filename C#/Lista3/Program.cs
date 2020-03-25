using System;

namespace Lista
{
    using Biblioteka;

    class Program
    {
        static void Main(string[] args)
        {

            Lista<int> l = new Lista<int>();
            Slownik<string, int> slo = new Slownik<string, int>();

            string s = "sss";

            slo.add("ssss", 5);
            



            l.addFirst(1);
            l.addFirst(2);
            l.addFirst(3);
            l.addLast(4);
            l.addLast(4); 
            l.addLast(4); 
            l.addLast(4);
            l.addFirst(8);
            l.PrintList();
            Console.WriteLine("Hello World!");
            l.removeFirst();
            l.removeLast();
            l.PrintList();

        }
    }
}
