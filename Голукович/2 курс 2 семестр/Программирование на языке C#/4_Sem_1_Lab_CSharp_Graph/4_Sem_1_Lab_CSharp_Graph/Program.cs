namespace _4_Sem_1_Lab_CSharp_Graph
{
    internal static class Program
    {
        /// <summary>
        ///  
        /// ����� ����������� ���� � ���� ��������,
        ///     �� ������� �� ��������� ����� �������,
        ///     ���� ���� �� �������� ����, ���� �� ��������)
        ///     
        /// ����, �� ������ ����� �� �������� ������� ��������, ��� ���� �� ���������
        ///     (IsCyclic ��� ����� ����� ������)
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