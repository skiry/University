USE TeaShop

-- Simple insert with multiple values, no need to specify the columns mapped to the values, all of them
-- are taken by default.
INSERT INTO Menus VALUES(2,20,6),(3,20,6)

-- The WHERE clause is there just for comic effect
SELECT * FROM Menus where 1=1

-- No id because of IDENTITY
INSERT INTO Ingredients( [name], [quantity] ) values ( 'fruit', 7 )

-- This doesn't make much sense because, although we do get the unique quantities from the ingredients,
-- all the rows will be selected because all contain quantity equal to one of the sub-selected one
SELECT * FROM Ingredients i WHERE i.quantity in (SELECT DISTINCT quantity FROM Ingredients)

-- Won't work due to FOREIGN KEY constraints unable to be satisfied
INSERT INTO Teas (name, price, mid ) values ( 'Lord Nelson', 10, 7 )

-- Should satisfy all the FOREIGN KEY and CHECK constraints.
INSERT INTO Teas VALUES ('Lord Nelson', 10, 1), ( 'Mint', 5, 1)

-- Hardest one so far
SELECT * FROM Teas

-- Insert into the pivot table ( the table that connects two tables through a many-to-many relationship ).
INSERT INTO Recipes ( Tid, Iid, UsedQuantity ) VALUES (4, 2, 1)

SELECT * FROM Recipes

-- Should be straightforward. Usually, a WHERE clause is  required in an update.
UPDATE Teas
	SET price = price + 2
	WHERE name = 'Mint'

-- That LIKE is similar to name matching regex ^f.*$
UPDATE Ingredients
	SET quantity = 2, name = 'such ingredient, very particle, wow'
	WHERE quantity > 2 OR name LIKE 'f%'

SELECT * FROM Ingredients

UPDATE Menus
	SET NoOfTeas = 3
	WHERE NoOfPages IN ( 2, 4, 6, 8 ) AND NoOfTeas IS NULL

UPDATE Teas
	SET Name = 'TeaName'
	WHERE Price BETWEEN 7 AND 10

-- The remarks which are, supposedly, very very important.
-- 1. Delete in the same order you drop tables, and as reversed for table creation and insertion.