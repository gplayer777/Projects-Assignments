namespace Projekt
{
class Program
    {
	using Biblioteka;
        static void Main(string[] args)
        {
        

            RandomWordStream rs = new RandomWordStream();
            for (int i = 0; i < 5; i++)
                Console.WriteLine(rs.next());


	    PrimeCollection primes = new PrimeCollection();
            primes.GetEnumerator().MoveNext();
		
		int k = 0;

		foreach (Prime p in primes)
		{
	           Console.WriteLine(p.val);
	           k++;
		   if (k == 10) break;
		}



		}
    }
    }
