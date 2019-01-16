function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 33198, y = 32876, z = 11},3222) and Game.isItemThere ({x = 33198, y = 32876, z = 11},3223) and Game.isItemThere ({x = 33198, y = 32876, z = 11},3224) and Game.isItemThere ({x = 33198, y = 32876, z = 11},3225) and Game.isItemThere ({x = 33198, y = 32876, z = 11},3226) and Game.isItemThere ({x = 33198, y = 32876, z = 11},3227) and Game.isItemThere ({x = 33198, y = 32876, z = 11},3228) then 
		Game.removeItemOnMap({x = 33198, y = 32876, z = 11}, 3222)
		Game.removeItemOnMap({x = 33198, y = 32876, z = 11}, 3223)
		Game.removeItemOnMap({x = 33198, y = 32876, z = 11}, 3224)
		Game.removeItemOnMap({x = 33198, y = 32876, z = 11}, 3225)
		Game.removeItemOnMap({x = 33198, y = 32876, z = 11}, 3226)
		Game.removeItemOnMap({x = 33198, y = 32876, z = 11}, 3227)
		Game.removeItemOnMap({x = 33198, y = 32876, z = 11}, 3228)
		Game.createItem(3229, 1, {x = 33198, y = 32876, z = 11})
		Game.sendMagicEffect({x = 33198, y = 32876, z = 11}, 7)
	end
end
