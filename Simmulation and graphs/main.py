import math
import pygame
import serial
from math import *
import matplotlib.pyplot as plt
import numpy as np
import pygame_plot
import re



WINDOW_HEIGHT =  600
WINDOW_WIDTH =  800
ROTATE_SPEED = 0.02
LEN_CUBE=0.5
window = pygame.display.set_mode( ( WINDOW_WIDTH,WINDOW_HEIGHT) )

GREEN=(69,139,0)
AXES=(69,139,116)
clock = pygame.time.Clock()

projection_matrix = [[1,0,0],
                     [0,1,0],
                     [0,0,0]]


#aici am pus punctele cubului, mijloacele laturilor si ale axelor 
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


#am conectat punctele pe ecran

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
    
    #am desenat axele, 
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

#aici e ce tine de accelorometru
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


gyro=list()

gyro_scale=0.2

file1 = open('data.txt', 'r')
Lines = file1.readlines()
tt=0
for data in Lines:
    try:
    #print(data)
        data_vector = data.split('\'')

        value=data_vector[1].split(':')
        result = []

        for item in value:
            result.append(item.split(' '))
        g=(float(result[3][3]),float(result[3][4]),float(result[3][5]))
   
        gyro.append(g)
        print(g)
        set_roll(float(gyro[-1][2])*gyro_scale)
        set_pitch(float(gyro[-1][0])*gyro_scale)
        set_yaw(float(gyro[-1][1])*gyro_scale)
    except:
        print("ERROR: "+data)
        
        continue
    pygame.event.get()
    window.fill((240,240,240))

#aici se calculeaza rotatia punctelor in functie de ce unghia are
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
    #aplicam rotatia pt fiecare punct
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


#desenam cubul
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
    
    #clock.tick(30)
    pygame.time.wait(200)
    pygame.display.update()

pygame.quit()
FONT_SIZE=25