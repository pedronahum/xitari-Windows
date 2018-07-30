using System;
using System.Collections.Generic;
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

            var screen = ale.ale_getRescaledYChannelScreenHistory();

            Console.WriteLine("Preprocessed Screen Size (4x84x84 grayscale images): {0}. ", screen.Count);
            //screen.ToList().ForEach(Console.WriteLine);

            //Check actions
            Console.WriteLine("Legal Actions: ");
            actions.ToList().ForEach(Console.WriteLine);
            //

            Console.WriteLine("Starting to Play...");
            sw.Start();
            const int numRollouts = 100;
            int steps = 0;
            var totalRewardArray = new List<double>();
            
            // Generate multiple rollouts
            for (var episode = 0; episode < numRollouts; episode++)
            {
                var totalReward = 0.0;
                while (!ale.ale_isGameOver())
                {
                    var reward = ale.ale_act(actions[rnd.Next(actions.Count)]);
                       
                    totalReward += reward;
                    
                    steps += 1;
                }
                
                Console.WriteLine("Episode {0} ended with score: {1} ", episode, totalReward);
                totalRewardArray.Add(totalReward);
                ale.ale_resetGame();
            }
            sw.Stop();
            Console.WriteLine("Elapsed={0} in {1} rollouts", sw.Elapsed, numRollouts);
            Console.WriteLine("Steps={0}" , steps);
            Console.WriteLine("Average Score: {0}; Max Score: {1} ", totalRewardArray.Average(), totalRewardArray.Max());

        }
    }
}
