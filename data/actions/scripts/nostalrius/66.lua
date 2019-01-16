function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32400, y = 32239, z = 06}, 432) then 
		item:transform(2773, 1)
		item:decay()
		Game.transformItemOnMap({x = 32400, y = 32239, z = 06}, 432, 408)
	elseif item:getId() == 2772 then
		item:transform(2773, 1)
		item:decay()
	elseif item:getId() == 2773 and Game.isItemThere({x = 32400, y = 32239, z = 06}, 408) then 
		item:transform(2772, 1)
		item:decay()
		Game.transformItemOnMap({x = 32400, y = 32239, z = 06}, 408, 432)
		doRelocate({x = 32400, y = 32239, z = 06},{x = 32400, y = 32239, z = 07})
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
	end
	return true
end