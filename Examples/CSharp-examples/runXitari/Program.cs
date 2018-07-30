using System;
using System.Diagnostics;
using System.Linq;
using Xitari;


namespace runXitari
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("======== Testing ALE in C# ========");
            var rnd = new Random();
            var sw = new Stopwatch();
            var ale = new Xitari.XitariALE("ms_pacman.bin");
            var totalActions = ale.ale_numLegalActions();
            var actions = ale.ale_legalActions((uint)totalActions);
            // Get the observartion
            var width = ale.ale_getScreenWidth();
            var height = ale.ale_getScreenHeight();
            Console.WriteLine("Width: {0} and Height: {1} of the screen ", width, height);
            var screen = ale.ale_getRescaledYChannelScreen();
            Console.WriteLine("Screen Size {0}: ", screen.Count);
            //Check actions
            actions.ToList().ForEach(Console.WriteLine);
            //
            sw.Start();
            const int totalEpisodes = 100;
            for (var episode = 0; episode < totalEpisodes; episode++)
            {
                var totalReward = 0.0;
                while (!ale.ale_isGameOver())
                {
                    
                    var reward = ale.ale_act(actions[rnd.Next(actions.Count)]);
                    //Console.WriteLine(reward);
                    
                    totalReward += reward;
                }
                // cout << "Episode " << episode << " ended with score: " << totalReward << endl;
                Console.WriteLine("Episode {0} ended with score: {1} ", episode, totalReward);
                ale.ale_resetGame();
            }
            sw.Stop();
            Console.WriteLine("Elapsed={0} in {1} episodes", sw.Elapsed, totalEpisodes);

        }
    }
}
