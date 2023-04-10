import math
import pygame
import serial
from math import *
import matplotlib.pyplot as plt
import numpy as np
import pygame_plot

WINDOW_HEIGHT =  400
WINDOW_WIDTH =  600
ROTATE_SPEED = 0.02
LEN_CUBE=0.5
window = pygame.display.set_mode( ( WINDOW_WIDTH,WINDOW_HEIGHT) )

GREEN=(69,139,0)
AXES=(69,139,116)
clock = pygame.time.Clock()

projection_matrix = [[1,0,0],
                     [0,1,0],
                     [0,0,0]]

cube_points = [n for n in range(20)]
cube_points[0] = [[-LEN_CUBE], [-2*LEN_CUBE], [LEN_CUBE]]
cube_points[1] = [[LEN_CUBE],[-2*LEN_CUBE],[LEN_CUBE]]
cube_points[2] = [[LEN_CUBE],[2*LEN_CUBE],[LEN_CUBE]]
cube_points[3] = [[-LEN_CUBE],[2*LEN_CUBE],[LEN_CUBE]]
cube_points[4] = [[-LEN_CUBE],[-2*LEN_CUBE],[-LEN_CUBE]]
cube_points[5] = [[LEN_CUBE],[-2*LEN_CUBE],[-LEN_CUBE]]
cube_points[6] = [[LEN_CUBE],[2*LEN_CUBE],[-LEN_CUBE]]
cube_points[7] = [[-LEN_CUBE],[2*LEN_CUBE],[-LEN_CUBE]]

cube_points[8] = [[0],[0],[LEN_CUBE]]
cube_points[9] = [[0],[0],[-LEN_CUBE]]
cube_points[10] = [[LEN_CUBE],[0],[0]]
cube_points[11] = [[-LEN_CUBE],[0],[0]]
cube_points[12] = [[0],[-2*LEN_CUBE],[0]]
cube_points[13] = [[0],[2*LEN_CUBE],[0]]


cube_points[14] = [[0],[0],[4*LEN_CUBE]]
cube_points[15] = [[0],[0],[-3*LEN_CUBE]]
cube_points[16] = [[4*LEN_CUBE],[0],[0]]
cube_points[17] = [[-3*LEN_CUBE],[0],[0]]
cube_points[18] = [[0],[-3*LEN_CUBE],[0]]
cube_points[19] = [[0],[4*LEN_CUBE],[0]]


def multiply_m(a, b):
    a_rows = len(a)
    a_cols = len(a[0])

    b_rows = len(b)
    b_cols = len(b[0])
    # Dot product matrix dimentions = a_rows x b_cols
    product = [[0 for _ in range(b_cols)] for _ in range(a_rows)]

    if a_cols == b_rows:
        for i in range(a_rows):
            for j in range(b_cols):
                for k in range(b_rows):
                    product[i][j] += a[i][k] * b[k][j]
    else:
        print("INCOMPATIBLE MATRIX SIZES")
    return product        


def connect_points(i, j, points,color):
    pygame.draw.line(window, color, (points[i][0], points[i][1]) , (points[j][0], points[j][1]),3)
class Point:
    # constructed using a normal tupple
    def __init__(self, point_t = (0,0)):
        self.x = float(point_t[0])
        self.y = float(point_t[1])
    # define all useful operators
    def __add__(self, other):
        return Point((self.x + other.x, self.y + other.y))
    def __sub__(self, other):
        return Point((self.x - other.x, self.y - other.y))
    def __mul__(self, scalar):
        return Point((self.x*scalar, self.y*scalar))
    def __div__(self, scalar):
        return Point((self.x/scalar, self.y/scalar))
    def __len__(self):
        return int(math.sqrt(self.x**2 + self.y**2))
    # get back values in original tuple format
    def get(self):
        return (self.x, self.y)
def draw_axes(i,j,points):
    dash_length=10
    origin = Point(points[i])
    target = Point(points[j])
    # print(origin)
    displacement = target - origin
    length = len(displacement)
    length+=1
    slope = Point((displacement.x/length,displacement.y/length))

    for index in range(0,int( length/dash_length), 2):
        start = origin + (slope *    index    * dash_length)
        end   = origin + (slope * (index + 1) * dash_length)
        pygame.draw.line(window, AXES, start.get(), end.get(), 1)
    pygame.draw.line(window,AXES,(points[i][0], points[i][1]) , (points[i+6][0], points[i+6][1]))
    #pygame.draw.line(window,(0,255,255),(points[j][0], points[j][1]) , (points[j+6][0], points[j+6][1]))
    
# Main Loop
scale = 100
angle_x = 0
angle_y = 0
angle_z = 0


def add_pitch(value):
    global angle_x
    angle_x=angle_x+value
def add_yaw(value):
    global angle_y
    angle_y= angle_y+value
def add_roll(value):
    global angle_z
    angle_z= angle_z+value
    
def set_pitch(value):
    global angle_x
    angle_x=value
def set_yaw(value):
    global angle_y
    angle_y=value
def set_roll(value):
    global angle_z
    angle_z=value

def cansat_simm():
    
    
    window.fill((240,240,240))

    rotation_x = [[1, 0, 0],
                    [0, cos(angle_x), -sin(angle_x)],
                    [0, sin(angle_x), cos(angle_x)]]

    rotation_y = [[cos(angle_y), 0, sin(angle_y)],
                    [0, 1, 0],
                    [-sin(angle_y), 0, cos(angle_y)]]

    rotation_z = [[cos(angle_z), -sin(angle_z), 0],
                    [sin(angle_z), cos(angle_z), 0],
                    [0, 0, 1]]

    points = [0 for _ in range(len(cube_points))]
    i = 0
    for point in cube_points:
        rotate_x = multiply_m(rotation_x, point)
        rotate_y = multiply_m(rotation_y, rotate_x)
        rotate_z = multiply_m(rotation_z, rotate_y)
        point_2d = multiply_m(projection_matrix, rotate_z)
    
        x = (point_2d[0][0] * scale) + WINDOW_WIDTH/2
        y = (point_2d[1][0] * scale) + WINDOW_HEIGHT/2

        points[i] = (x,y)
        i += 1
        #pygame.draw.circle(window, (255, 0, 0), (x, y), 5)

    connect_points(0, 1, points,GREEN)
    connect_points(0, 3, points,GREEN)
    connect_points(0, 4, points,GREEN)
    connect_points(1, 2, points,GREEN)
    connect_points(1, 5, points,GREEN)
    connect_points(2, 6, points,GREEN)
    connect_points(2, 3, points,GREEN)
    connect_points(3, 7, points,GREEN)
    connect_points(4, 5, points,GREEN)
    connect_points(4, 7, points,GREEN)
    connect_points(6, 5, points,GREEN)
    connect_points(6, 7, points,GREEN)
    connect_points(0, 2, points,(255, 0, 255))
    connect_points(1, 3, points,(255, 0, 255))
    

    draw_axes(8,9,points)
    draw_axes(10,11,points)
    draw_axes(12,13,points)
    
    
    # #citim datele si le adaugam cum le primim
    # for event in pygame.event.get():
    #     if event.type == pygame.QUIT:
    #         pygame.quit()
    #     keys = pygame.key.get_pressed()
    #     if keys[pygame.K_r]:
    #         set_pitch(0)
    #         set_roll(0)
    #         set_yaw(0)
    #     if keys[pygame.K_a]:
    #         add_yaw(ROTATE_SPEED)
    #     if keys[pygame.K_d]: 
    #         add_yaw(-ROTATE_SPEED)    
    #     if keys[pygame.K_w]:
    #         add_pitch(ROTATE_SPEED)
    #     if keys[pygame.K_s]:
    #         add_pitch(-ROTATE_SPEED)
    #     if keys[pygame.K_q]:
    #         add_roll(-ROTATE_SPEED)
    #     if keys[pygame.K_e]:
    #         add_roll(ROTATE_SPEED)      
          
    pygame.display.flip()

COLOR_PLOT='xkcd:mint green'
tmp=100
plt.ion()
fig=plt.figure(figsize=(10,6))
fig.patch.set_facecolor(COLOR_PLOT)
fig.tight_layout()
ax1 =plt.subplot2grid((2,4),(0,0),colspan=1,fig=fig)
ax2 =plt.subplot2grid((2,4),(1,0),colspan=1,fig=fig)
ax3 =plt.subplot2grid((2,4),(0,1),colspan=1,fig=fig)
ax_Text =plt.subplot2grid((2,4),(1,1),colspan=1,fig=fig)
ax4 =plt.subplot2grid((2,4),(0,2),colspan=2,rowspan=2,fig=fig,aspect='equal')

ax1.set_facecolor(COLOR_PLOT)
ax2.set_facecolor(COLOR_PLOT)
ax3.set_facecolor(COLOR_PLOT)
ax4.set_facecolor(COLOR_PLOT)
ax_Text.set_facecolor(COLOR_PLOT)

ax4.set_xlabel('latitude')
ax4.set_ylabel('longitude')
#fig.set_size_inches((WINDOW_WIDTH/2, WINDOW_HEIGHT/2))
i=0
time=list()
temperature=list()
humidity=list()
pression=list()

time.append(0)
temperature.append(0)
humidity.append(0)
pression.append(0)

def draw_graphs():    
        #goleste plotul ca sa aiba ultimele 50 valori

    color='red'
    
    time.append(i-1)
    temperature.append(i)

    ax1.plot(time,temperature,color='red')
    ax1.set_title("Temperature Sensor")
    
    
    ax2.plot(time,temperature,color='red')
    ax2.set_title("Humidity Sensor")
    
    
    ax3.plot(time,temperature,color='red')
    ax3.set_title("Pression  Sensor")
    
    ax_Text.text(0.05, 0.95, "text",fontsize=14,
        verticalalignment='top')
    ax_Text.get_xaxis().set_visible(False) 
    ax_Text.get_yaxis().set_visible(False)
    ax_Text.axis('off')
    plt.show()
    plt.pause(0.0001)


# ser=serial.Serial("COM12",115200)
# ser.close()
# ser.open()

# def split_data():
#     data=ser.readline()
#     decoded_data=data.decode()
while True:
    clock.tick(60)
    
    cansat_simm()
    draw_graphs()
    add_pitch(0.1)
    i+=1
   
