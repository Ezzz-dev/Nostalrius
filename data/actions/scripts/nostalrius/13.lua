function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32568, y = 32078, z = 12},2185) and Game.isItemThere ({x = 32569, y = 32078, z = 12},2185) then
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 32568, y = 32078, z = 12}, 2185)
		Game.removeItemOnMap({x = 32569, y = 32078, z = 12}, 2185)
	elseif item:getId() == 2773 and Game.isItemThere({x = 32568, y = 32078, z = 12},2185) and Game.isItemThere ({x = 32569, y = 32078, z = 12}, 2185) then 
		item:transform(2772, 1)
		item:decay()
	elseif item:getId() == 2773 then
		item:transform(2772, 1)
		item:decay()
		Game.createItem(2185, 1, {x = 32568, y = 32078, z = 12})
		Game.createItem(2185, 1, {x = 32569, y = 32078, z = 12})
	end
	return true
end