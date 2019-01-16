function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32790, y = 31594, z = 07},1772) then 
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 32790, y = 31594, z = 07}, 1772)
	elseif item:getId() == 2773 and Game.isItemThere({x = 32790, y = 31594, z = 07}, 1772) then
		item:transform(2772, 1)
		item:decay()
	elseif item:getId() == 2773 then
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32790, y = 31594, z = 07},{x = 32790, y = 31595, z = 07})
		Game.createItem(1772, 1, {x = 32790, y = 31594, z = 07})
	end
	return true
end