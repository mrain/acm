uses
        math;

const
	maxn=20;
        max_num=1e10;
        eps=1e-6;

type
        extended=real;
	Tdot=record x,y,z:extended; end;

var
	dot:array[1..maxn]of Tdot;
	n:longint;
	maxdis:extended;

procedure setup;
begin
	assign(input,'input.txt'); reset(input);
end;

procedure endit;
begin
	close(input); close(output);
end;

procedure init;
var	i:longint;
        lat,lon:extended;
begin
	readln(n);
	for i:=1 to n do
	begin
		read(lat,lon);
		lat:=lat/180*pi; lon:=lon/180*pi;
		dot[i].x:=cos(lat)*cos(lon);
		dot[i].y:=cos(lat)*sin(lon);
		dot[i].z:=sin(lat);
	end;
end;

function line_dist(a,b:Tdot):extended;
begin	exit(sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)+sqr(a.z-b.z))); end;

function sphere_dist(a,b:Tdot):extended;
var	t:extended;
begin
	t:=line_dist(a,b); t:=t/2;
	if t>1 then t:=1;
	exit(2*arcsin(t));
end;

operator -(a,b:Tdot) c:Tdot;
begin	c.x:=a.x-b.x; c.y:=a.y-b.y; c.z:=a.z-b.z; end;

operator *(a,b:Tdot) c:Tdot;
begin
	c.x:=a.y*b.z-a.z*b.y;
	c.y:=a.z*b.x-a.x*b.z;
	c.z:=a.x*b.y-a.y*b.x;
end;

procedure normalize(var a:Tdot);
var	dist:extended;
begin
	dist:=sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
	a.x:=a.x/dist; a.y:=a.y/dist; a.z:=a.z/dist;
end;

function getmid(a,b:Tdot):Tdot;
var     c:Tdot;
begin
        c.x:=a.x+b.x; c.y:=a.y+b.y; c.z:=a.z+b.z;
        if (abs(c.x)<eps) and (abs(c.y)<eps) and (abs(c.z)<eps) then
	        if a.x<1-eps then
    		    begin c.x:=0; c.y:=-a.z; c.z:=a.y; end 
			else
	    	    if a.y<1-eps then
			        begin c.x:=-a.z; c.y:=0; c.z:=a.x; end 
				else
			        begin c.x:=-a.y; c.y:=a.x; c.z:=0; end
        else assert(false);
        normalize(c); exit(c);
end;

procedure chk(a:Tdot);
var	i:longint;
        t,mindis:extended;
begin
        mindis:=max_num;
	for i:=1 to n do
	begin
		t:=sphere_dist(a,dot[i]);
                if t<mindis then mindis:=t;
        end;
        if mindis>maxdis then maxdis:=mindis;
end;

procedure main;
var	i,j,k:longint;
	t:Tdot;
begin
	if n=1 then begin writeln(pi:0:6); exit; end;
	maxdis:=0;
        for i:=1 to n-1 do
                for j:=i+1 to n do
                begin
                        t:=getmid(dot[i],dot[j]);
                        normalize(t);
                        chk(t);
                        t.x:=-t.x; t.y:=-t.y; t.z:=-t.z;
                        chk(t);
                end;
	for i:=1 to n-2 do
		for j:=i+1 to n-1 do
			for k:=j+1 to n do
			begin
				t:=(dot[j]-dot[i])*(dot[k]-dot[i]);
				normalize(t);
				chk(t);
                                t.x:=-t.x; t.y:=-t.y; t.z:=-t.z;
                                chk(t);
			end;
	writeln(maxdis:0:6);
end;

begin
	setup;
	init;
	main;
	endit;
end.
