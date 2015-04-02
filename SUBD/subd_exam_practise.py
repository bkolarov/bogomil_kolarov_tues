# -*- coding: utf-8 -*-
import sqlite3 as lite

RELATION_ONE_TO_ONE = 1
RELATION_ONE_TO_MANY = 2
RELATION_MANY_TO_MANY = 3

def readTableColumnNames():
	cols = []
	
	print 'Enter names of the columns and there type in the following format: columnName:type.\nPress enter after each name. Enter \"end of input\" to finish.\n'
	
	while 1:
		colName = raw_input()

		if colName == 'end of input':
			break
		
		cols.insert(len(cols), colName)
	
	return cols

def getColumnsAndTypesOfTable(tableName, con):
	result = ''
	records = executeQuery('PRAGMA table_info(' + tableName + ')', con).fetchall()
	result += records[0][1] + ' ' + records[0][2]
	records.pop(0)
	for record in records:
		result += ', '
		result += record[1] + ' ' + record[2]

	return result	

def getColumnsOfTable(tableName, con):
	result = ''
	records = executeQuery('PRAGMA table_info(' + tableName + ')', con).fetchall()
	result += records[0][1].replace('INTEGER', 'INTEGER PRIMARY KEY')
	records.pop(0)
	for record in records:
		result += ', '
		result += record[1]

	return result	

def parseColumnNames(cols):
	sqlCols = ''
	
	sqlCols += cols[0].replace(':', ' ')

	cols.pop(0)
	for column in cols:
		sqlCols += ', '
		sqlCols += column.replace(':', ' ')		
	
	print sqlCols
	
	return sqlCols

def addColumnToTable(tableName, columnName, columnType, con):

	if columnExists(tableName, columnName, con):
		return
		
	query = 'alter TABLE ' + tableName + ' RENAME TO tempOldTable'
	executeQuery(query, con)
	query = 'CREATE TABLE ' + tableName + '(' + getColumnsAndTypesOfTable('tempOldTable', con) + ', ' + columnName + ' ' + columnType + ')'
	executeQuery(query, con)
	columnsOfTable = getColumnsOfTable('tempOldTable', con)
	query = 'INSERT INTO ' + tableName + ' (' + columnsOfTable + ') SELECT ' + columnsOfTable + ' FROM tempOldTable'
	executeQuery(query, con)
	query = 'DROP TABLE tempOldTable'
	executeQuery(query, con)
	
	

def columnExists(tableName, columnName, con):
	columns = [i[1] for i in executeQuery('PRAGMA table_info(' + tableName + ')', con)]

	if columnName not in columns:
		return False
	else:		
		return True

def addConnectionColumn(tableName, connectedToTableName, con):
	columnName = connectedToTableName + '_Id'
	
	if columnExists(tableName, columnName, con):
		return
	
	query = 'alter TABLE ' + tableName + ' ADD COLUMN FOREIGN KEY(' + columnName + ') REFERENCES ' + tableName + '(Id)'
	executeQuery(query, con)

def createOneToManyRelation(table1, table2, con):
	addColumnToTable(table2, table1 + '_Id', 'INTEGER', con)
	addColumnToTable(table2, 'FOREIGN KEY(' + table1 + '_Id) ', 'REFERENCES ' + table1 + '(Id)', con)
	
def createOneToOneRelation(table1, table2, con):
	addColumnToTable(table1, table2 + '_Id', 'INTEGER', con)
	addColumnToTable(table1, 'FOREIGN KEY(' + table2 + '_Id) ', 'REFERENCES ' + table2 + '(Id)', con)
	addColumnToTable(table2, table1 + '_Id', 'INTEGER', con)
	addColumnToTable(table2, 'FOREIGN KEY(' + table1 + '_Id) ', 'REFERENCES ' + table1 + '(Id)', con)

def createRelation(table1, table2, relationCode, con):
	if relationCode == RELATION_ONE_TO_ONE:
		createOneToOneRelation(table1, table2, con)
	elif relationCode == RELATION_ONE_TO_MANY:
		createOneToManyRelation(table1, table2, con)
#	elif relationCode == RELATION_MANY_TO_MANY:

def createTable(con):
	query = 'CREATE TABLE '
	
	tableName = raw_input('Enter the name of the table.\n')

	executeQuery('DROP TABLE IF EXISTS ' + tableName, con)

	query += tableName + '(Id INTEGER PRIMARY KEY, '

	cols = readTableColumnNames()
	
	query += parseColumnNames(cols) + ')'
	
	executeQuery(query, con)

def executeQuery(query, con):
	query += ';'
	print query
	cursor = con.cursor()
	result = cursor.execute(query)
	con.commit()
	
	return result
	
def createTables(con):
	numTables = int(raw_input('Enter the number of tables.\n'))

	count = 0
	while count < numTables:
		createTable(con)
		count += 1
		
def createRelations(con):
	createRelation('Category', 'User', RELATION_ONE_TO_MANY, con)
	createRelation('Category', 'Article', RELATION_ONE_TO_MANY, con)
	createRelation('Article', 'Tag', RELATION_ONE_TO_ONE, con)

con = lite.connect('SUBD_exam.db')
#createTables(con)
createRelations(con)


con.close()
