namespace chess
{
    public interface Piece
    {
        void Move();
        void Capture(Piece target);
        void Remove();
    }
}
