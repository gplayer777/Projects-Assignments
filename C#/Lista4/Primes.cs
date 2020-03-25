using System;
using System.Collections;

namespace Biblioteka
{

    class PrimeEnum : IEnumerator
    {
        public Prime prime;

        public const int MaxValue = 2147483647;


        PrimeEnum()
        {
            prime = new Prime();
        }

        public Boolean isPrime(int p)
        {
            if (p < 2)
                return false;

            for (int i = 2; i * i <= p; i++)
                if (p % i == 0)
                    return false;

            return true;


        }



        public PrimeEnum(Prime prime)
        {
            this.prime = prime;
        }

        public bool MoveNext()
        {

            if (prime.val < MaxValue)
                prime.val++;


            while ((!isPrime(prime.val)))
            {
                prime.val++;

            }

            return prime.val < MaxValue;
        }

    

        object IEnumerator.Current
        {

        get
        {
            return Current;
        }
            
        }

        public Prime Current
        {
            get
            {
                return prime;
            }
        }


        public void Reset()
        {
            prime.val = -1;
        }




    }

    public class Prime
    {
        public int val = -1;

    }

    public class PrimeCollection : IEnumerable
    {

        Prime prime;

        public PrimeCollection()
        {
            prime = new Prime();
        }

        public IEnumerator GetEnumerator()
        {
            return new PrimeEnum(prime);
        }
    }


    
}
