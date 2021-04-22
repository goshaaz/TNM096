import random
import sys
import numpy as np
import math
from copy import deepcopy

def solution_preferences(max_steps):
    solutions = []
    solutions_preferences = []
    for i in range(max_steps):
        classes = [['MT101'], ['MT102'], ['MT103'],['MT104'], ['MT105'], ['MT106'],['MT107'],
        ['MT201'], ['MT202'], ['MT203'], ['MT204'], ['MT205'], ['MT206'],
        ['MT301'], ['MT302'], ['MT303'], ['MT304'], ['MT401'], ['MT402'], ['MT403'],
        ['MT501'], ['MT502'], [], []]

        random.shuffle(classes)

        csp = np.asarray(classes).reshape(8,3)

        solution = min_conflicts(csp, 100)

        if solution != None:
            pref_value = calculatePreferences(solution)
            solutions_preferences.append(pref_value)
            solutions.append(solution)  
    min_value = min(solutions_preferences)
    min_index = solutions_preferences.index(min_value)
    print(solutions_preferences)
    print("Solution with preferences: ")
    return solutions[min_index]

def toStringArray(arr):
    stringarr = []
    for i in range(8):
        for j in range(3):
            if arr[i][j] == []:
                stringarr.append('')
            else:
                stringarr.append(arr[i][j][0])
    return stringarr        

def calculatePreferences(state):
    conflicts = 0
    if state[0][0] != []:
        conflicts += 1
    if state[0][1] != []:
        conflicts += 1
    if state[0][2] != []:
        conflicts += 1
    if state[3][0] != []:
        conflicts += 1
    if state[3][1] != []:
        conflicts += 1
    if state[3][2] != []:
        conflicts += 1
    if state[7][0] != []:
        conflicts += 1
    if state[7][1] != []:
        conflicts += 1
    if state[7][2] != []:
        conflicts += 1
    
    strarray = toStringArray(state)
    idxof_501 = strarray.index('MT501')
    idxof_502 = strarray.index('MT502')

    if idxof_501 != 12 and idxof_501 != 13 and idxof_501 != 14 and idxof_501 != 15 and idxof_501 != 16 and idxof_501 != 17:
        conflicts += 1
    if idxof_502 != 12 and idxof_502 != 13 and idxof_502 != 14 and idxof_502 != 15 and idxof_502 != 16 and idxof_502 != 17:
        conflicts += 1    
    return conflicts                                        

def min_conflicts(initialstate,max_steps):
    current = initialstate
    for x in range(max_steps):
        if getConflictedPositions(current) == []:
            return current
        random_conflicted_pos = random.choice(getConflictedPositions(current))
        randompos_i = random_conflicted_pos[0]
        randompos_j = random_conflicted_pos[1]
        if len(current[randompos_i][randompos_j]) > 1:
            rand_idx = random.randrange(len(current[randompos_i][randompos_j]))
            h_values = []
            for i in range(8):
                for j in range(3):
                    potential_state = deepcopy(current) 
                    chosen_value = current[randompos_i][randompos_j][rand_idx]
                    potential_state[randompos_i][randompos_j].remove(chosen_value)
                    potential_state[i][j].append(chosen_value)
                    conflict_current = calculateConflicts(potential_state)
                    if i == randompos_i and j == randompos_j:
                        h_values.append(sys.maxsize)
                    else:
                        h_values.append(conflict_current)  
            min_value = min(h_values)
            min_index = h_values.index(min_value)
            #Get i and j position from min_index
            idx = 0
            timetobreak = False
            for i in range(8):
                for j in range(3):
                    if idx == min_index:
                        newpos = [i, j]
                        timetobreak = True
                        break
                    idx = idx + 1
                if timetobreak == True:
                    break            
            current_value = deepcopy(current[randompos_i][randompos_j])[rand_idx]
            current_copy = deepcopy(current)
            current_copy[randompos_i][randompos_j].remove(current_value)
            current_copy[newpos[0]][newpos[1]].append(current_value)
            current = current_copy    
            if min_value == 0:
                return current          
        else:
            h_values = []
            for i in range(8):
                for j in range(3):
                    potential_state = deepcopy(current)
                    chosen_value = current[randompos_i][randompos_j][0]
                    potential_state[randompos_i][randompos_j].remove(chosen_value)
                    potential_state[i][j].append(chosen_value)
                    conflict_current = calculateConflicts(potential_state)
                    if i == randompos_i and j == randompos_j:
                        h_values.append(sys.maxsize)
                    else:
                        h_values.append(conflict_current)
            min_value = min(h_values)
            min_index = h_values.index(min_value)
            #Get i and j position from min_index
            idx = 0
            timetobreak = False
            for i in range(8):
                for j in range(3):
                    if idx == min_index:
                        newpos = [i, j]
                        timetobreak = True
                        break
                    idx = idx + 1
                if timetobreak == True:
                    break            
            current_value = deepcopy(current[randompos_i][randompos_j])[0]
            current_copy = deepcopy(current)
            current_copy[randompos_i][randompos_j].remove(current_value)
            current_copy[newpos[0]][newpos[1]].append(current_value)
            current = current_copy
            if getConflictedPositions(current) == []:
                return current 

def getConflictedPositions(state):
    confl_arr = []
    for i in range(8):
        for j in range(3):
            if len(state[i][j]) == 1:
                if j == 0:
                    if state[i][1] != []:
                        if len(state[i][1]) > 1:
                            for idx in range(len(state[i][1])):
                                if state[i][1][idx][2] == state[i][j][0][2] and state[i][j][0][2] != '5':
                                    confl_arr.append([i,j])
                                    break
                        else:
                            if state[i][1][0][2] == state[i][j][0][2] and state[i][j][0][2] != '5':
                                confl_arr.append([i,j])  
                              
                    if state[i][2] != []:
                        if len(state[i][2]) > 1:
                            for idx in range(len(state[i][2])):
                                if state[i][2][idx][2] == state[i][j][0][2] and state[i][j][0][2] != '5':
                                    confl_arr.append([i,j])
                                    break
                        else:
                            if state[i][2][0][2] == state[i][j][0][2] and state[i][j][0][2] != '5':
                                confl_arr.append([i,j])  
                                 
                if j == 1:
                    if state[i][0] != []:
                        if len(state[i][0]) > 1:
                            for idx in range(len(state[i][0])):
                                if state[i][0][idx][2] == state[i][j][0][2] and state[i][j][0][2] != '5':
                                    confl_arr.append([i,j])
                                    break
                        else:
                            if state[i][0][0][2] == state[i][j][0][2] and state[i][j][0][2] != '5':
                                confl_arr.append([i,j])  
                                 
                    if state[i][2] != []:
                        if len(state[i][2]) > 1:
                            for idx in range(len(state[i][0])):
                                if state[i][0][idx][2] == state[i][j][0][2] and state[i][j][0][2] != '5':
                                    confl_arr.append([i,j])
                                    break
                        else:
                            if state[i][2][0][2] == state[i][j][0][2] and state[i][j][0][2] != '5':
                                confl_arr.append([i,j])  
                                  
                if j == 2:
                    if state[i][0] != []:
                        if len(state[i][0]) > 1:
                            for idx in range(len(state[i][0])):
                                if state[i][0][idx][2] == state[i][j][0][2] and state[i][j][0][2] != '5':
                                    confl_arr.append([i,j])
                                    break
                        else:
                            if state[i][0][0][2] == state[i][j][0][2] and state[i][j][0][2] != '5':
                                confl_arr.append([i,j])  
                               
                    if state[i][1] != []:
                        if len(state[i][1]) > 1:
                            for idx in range(len(state[i][1])):
                                if state[i][1][idx][2] == state[i][j][0][2] and state[i][j][0][2] != '5':
                                    confl_arr.append([i,j])
                                    break
                        else:
                            if state[i][1][0][2] == state[i][j][0][2] and state[i][j][0][2] != '5':
                                confl_arr.append([i,j])  
                                      
            elif len(state[i][j]) > 1:
                confl_arr.append([i,j])
    return confl_arr
def calculateConflicts(state):
    conflicts = 0
    for i in range(8):
        for j in range(3):
            n_elements = len(state[i][j])
            if n_elements == 0 or n_elements == 1:
                conflicts += 0
            else:
                n_combinations = (math.factorial(n_elements))/(2*math.factorial(n_elements-2))
                conflicts += n_combinations
    for row in range(8):
        #Compare first column with second column
        n_elements_first_column = len(state[row][0])
        n_elements_second_column = len(state[row][1])
        if n_elements_first_column != 0:
            for col1 in range(n_elements_first_column):
                for col2 in range(n_elements_second_column):
                    if state[row][0][col1][2] == state[row][1][col2][2] and state[row][0][col1][2] != "5":
                        conflicts += 1
        #Compare second column with third column
        n_elements_second_column = len(state[row][1])
        n_elements_third_column = len(state[row][2])
        if n_elements_second_column != 0:
            for col1 in range(n_elements_second_column):
                for col2 in range(n_elements_third_column):
                    if state[row][1][col1][2] == state[row][2][col2][2] and state[row][1][col1][2] != "5":
                        conflicts += 1        
        #Compare first column with third column
        n_elements_first_column = len(state[row][0])
        n_elements_third_column = len(state[row][2])
        if n_elements_first_column != 0:
            for col1 in range(n_elements_first_column):
                for col2 in range(n_elements_third_column):
                    if state[row][0][col1][2] == state[row][2][col2][2] and state[row][0][col1][2] != "5":
                        conflicts += 1   
    return conflicts                                         




classes = [['MT101'], ['MT102'], ['MT103'],['MT104'], ['MT105'], ['MT106'],['MT107'],
['MT201'], ['MT202'], ['MT203'], ['MT204'], ['MT205'], ['MT206'],
['MT301'], ['MT302'], ['MT303'], ['MT304'], ['MT401'], ['MT402'], ['MT403'],
['MT501'], ['MT502'], [], []]

random.shuffle(classes)

classes = np.asarray(classes).reshape(8,3)

#print(min_conflicts(classes, 50))

print(solution_preferences(300))