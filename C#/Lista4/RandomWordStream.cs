using System;
using System.Text;

namespace Biblioteka
{

    interface Stream
    {
        public int next();
        public bool eos();


    }


    class IntStream: Stream
    {
        protected bool end;
        protected int val;

        public IntStream()
        {
            this.val = -1;
        }



        virtual public void reset()
        {
            this.end = false;
            this.val = -1;
        }

        virtual public bool eos(){
            this.end = true;
            return end;
        }

        virtual public int next()
        {
            this.val += 1;
            return val;
        }






    }

    class PrimeStream : IntStream, Stream
    {
        protected int c;
        protected bool end;

        public const int MaxValue = 2147483647;

        private bool isPrime(int p)
        { 
           if (p < 2)
           return false;
            
            for(int i = 2; (i*i)<=p; i++)
                if (p % i == 0) 
                  return false;
           
             return true;

        }

        public override int next()
        {
            if (c < MaxValue)
                c++;

           
            while ((!isPrime(c) ) && (c < MaxValue))
            {
                c++;
               
            }


            if (!isPrime(c))
            {
                eos();
                return -1;


            }



            return c;
        }

        public override bool eos()
        {
            end = true;
            return end;
        }


    }

    class RandomStream : IntStream, Stream
    {
        private Random rnd;

        public RandomStream()
        {
            this.rnd = new Random();
        }

        public override int next()
        {    
            return rnd.Next(97, 123);
        }


    }

    class RandomWordStream : IntStream
    {

        private RandomStream rs;
        private PrimeStream ps;
        private String word;
        private int length;
        

        public RandomWordStream()
        {
            this.rs = new RandomStream(); // 97 122
            this.ps = new PrimeStream();

        }
        public string next()
        {
            word = "";
            length = 0;


            length += ps.next();

            Console.WriteLine(length);
            for(int i = 0; i < length; i++)
            {
               word = word.Insert(i,  ((char)rs.next()).ToString());
            }

            return word;
        }

        public override void reset()
        {
            base.reset();
        }

        public override bool eos()
        {
            return base.eos();
        }



    }

    
}
