function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32259, y = 31891, z = 10},2129) then
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 32259, y = 31891, z = 10}, 2129)
	elseif item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
	elseif item:getId() == 2773 and Game.isItemThere({x = 32259, y = 31891, z = 10}, 2129) then 
		item:transform(2772, 1)
		item:decay()
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32259, y = 31891, z = 10},{x = 32259, y = 31892, z = 10})
		Game.createItem(2129, 1, {x = 32259, y = 31891, z = 10})
	end
	return true
end