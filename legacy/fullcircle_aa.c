
/*

void render_full_circle_with_aa(t_win *win, t_pixel centre, int radius, int color)
{

	int centreX = centre.x;
	int centreY = centre.y;
    int radius2 = radius * radius;

    // Upper and lower halves
    int quarter = round(radius2 / sqrt(radius2 + radius2));
    for (int x = 0; x <= quarter; x++) {
        float y = radius * sqrt(1 - x * x / (float)radius2);
        float error = y - (int)(y);

        setPixel4(win, centreX, centreY, x, (int)(y), color, error, true);
		setPixel4(win, centreX, centreY, (int)(y), x, color, error, true);
        setPixel4(win, centreX, centreY, x, (int)(y) + 1, color, 1.0f - error, false);
		setPixel4(win, centreX, centreY, (int)(y) + 1, x, color, 1.0f - error, false);
    }
}


*/
