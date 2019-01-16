function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32266, y = 31860, z = 11},2129) then 
		Game.removeItemOnMap({x = 32266, y = 31860, z = 11}, 2129)
		Game.transformItemOnMap({x = 32266, y = 31860, z = 11}, 410, 411)
		item:transform(2773, 1)
		item:decay()
	elseif item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
	elseif item:getId() == 2773 and Game.isItemThere({x = 32266, y = 31860, z = 11}, 2129) then
		item:transform(2772, 1)
		item:decay()
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		Game.transformItemOnMap({x = 32266, y = 31860, z = 11}, 411, 410)
		Game.createItem(2129, 1, {x = 32266, y = 31860, z = 11})
	end
	return true
end