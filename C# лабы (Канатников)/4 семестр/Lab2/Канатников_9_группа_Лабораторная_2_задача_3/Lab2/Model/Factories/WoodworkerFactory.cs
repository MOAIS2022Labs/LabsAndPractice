namespace Lab2Construction.Model.Factories
{
    public class WoodworkerFactory : StaffFactory
    {
        public WoodworkerFactory(int x, int y, int id) : base(x, y, id)
        {
        }

        public WoodworkerFactory(Point location, int id) : base(location, id) { }

        public override Staff CreateStaff()
        {
            var woodworker = new Woodworker(location, id);
            return woodworker;
        }
    }
}
