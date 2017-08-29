using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Xitari.XitariALE;

namespace runXitari
{
    class Program
    {
        static void Main(string[] args)
        {
            var ale = new Xitari.XitariALE("pong.bin");
            var totalActions = ale.ale_numLegalActions();
            var legalActions = new int[totalActions];
            Console.WriteLine(totalActions);
        }
    }
}
