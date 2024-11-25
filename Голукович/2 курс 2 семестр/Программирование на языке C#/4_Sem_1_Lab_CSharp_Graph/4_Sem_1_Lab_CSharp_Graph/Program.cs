namespace _4_Sem_1_Lab_CSharp_Graph
{
    internal static class Program
    {
        /// <summary>
        ///  
        /// самая бесполезная лаба в этом семестре,
        ///     на которую вы потратите много времени,
        ///     пока либо не сделаете сами, либо не скатаете)
        ///     
        /// кста, не уверен верно ли работает функция проверки, что граф не замкнутый
        ///     (IsCyclic для обоих видов графов)
        /// 
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            Application.Run(new Form_Graph());
        }
    }
}