class Cuadrado
{
public:
	int
int pertenece(int x, int y, cuadrado* cua)
{
	int cx =cua->x;
	int cy =cua->y;
	int csize =cua->size;
	if( (x>=cx) && (x<(cx+csize)) && (y>=cy) && (y<(cy+csize)) )
	{
		return 1;
	}
	return 0;
}

int pertenece_borde_sup(int x, int y, cuadrado* cua)
{
	int cx = cua->x;
	int cy = cua->y;
	int csize = cua->size;
	if( (y>=cy) && (y<(cy+csize)) && (x==cx) )
	{
		return 1;
	}
	return 0;
}

int pertenece_borde_inf(int x, int y, cuadrado* cua)
{
	int cx = cua->x;
	int cy = cua->y;
	int csize = cua->size;
	if ( (y>=cy) && (y<(cy+csize)) && (x==(cx+csize-1)) )
	{
		return 1;
	}
	return 0;
}
