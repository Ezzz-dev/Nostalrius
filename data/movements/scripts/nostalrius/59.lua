function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 32476, y = 31900, z = 05},2471) and not Game.isItemThere ({x = 32478, y = 31904, z = 05}, 1948) then 
		Game.createItem(1948, 1, {x = 32478, y = 31904, z = 05})
		Game.transformItemOnMap({x = 32476, y = 31900, z = 05}, 431, 430)
	elseif Game.isItemThere({x = 32476, y = 31900, z = 05}, 2471) then
		Game.transformItemOnMap({x = 32476, y = 31900, z = 05}, 431, 430)
	end
end

function onRemoveItem(item, tileitem, position)
	if Game.isItemThere({x = 32478, y = 31904, z = 05},1948) then 
		Game.removeItemOnMap({x = 32478, y = 31904, z = 05}, 1948)
		Game.transformItemOnMap({x = 32476, y = 31900, z = 05}, 430, 431)
	else
		Game.transformItemOnMap({x = 32476, y = 31900, z = 05}, 430, 431)
	end
end
