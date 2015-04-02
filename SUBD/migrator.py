import sqlite3 as lite

def createTable(name, columns, con):
	dropTable(name, con)
	query = 'CREATE TABLE ' + name + ' (Id, ' + columns + ')'
	executeQuery(query, con)

def insertIntoTableFromTable(intoTableName, columns, fromTableName, con):
	query = 'INSERT INTO TABLE ' + intoTableName + ' ' + columns + ' SELECT ' + columns + ' FROM ' + fromTableName

def dropTable(tableName, con):
	executeQuery('DROP TABLE IF EXISTS ' + tableName, con)

def migrate(newTableName1, newTableName2, columnsTable1, columnsTable2, oldTable, con):
	createTable(newTableName1, columnsTable1, con)
	createTable(newTableName2, columnsTable2, con)
	
	insertIntoTableFromTable(newTableName1, columnsTable1, oldTable, con)
	insertIntoTableFromTable(newTableName2, columnsTable2, oldTable, con)
	
def executeQuery(query, con):
	query += ';'
	print query
	cursor = con.cursor()
	result = cursor.execute(query)
	con.commit()
	
	return result

con = lite.connect('SUBD_exam.db')
migrate('Category_part1', 'Category_part2', 'created_by', 'name', 'Category', con)
dropTable('Category', con)
con.close()
