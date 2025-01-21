minx = miny = 200000000000000
maxx = maxy = 400000000000000

def valid(hailstone0, hailstone1):
    # Returns true if the two hailstones may collide
    # in the future in the expected area.
    # hailstone format: ((x, y, z), (dx, dy, dz))
    p0, v0 = hailstone0
    x0, y0, z0 = p0
    dx0, dy0, dz0 = v0
    p1, v1 = hailstone1
    x1, y1, z1 = p1
    dx1, dy1, dz1 = v1

    x0(t) = x0 + dx0 * t
    x1(t) = x1 + dx1 * t
    y0(t) = y0 + dy0 * t
    y1(t) = y1 + dy1 * t

    t0, t1 = var('t0 t1')
    
    ans = solve([
        x0(t=t0) == x1(t=t1),
        y0(t=t0) == y1(t=t1),
        minx <= x0(t=t0) <= maxx,
        miny <= y0(t=t0) <= maxy,
        t0 >= 0,
        t1 >= 0
    ], t0, t1)
    return len(ans) > 0