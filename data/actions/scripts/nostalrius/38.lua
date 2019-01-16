function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 32566, y = 32119, z = 07}, 1270)
		Game.transformItemOnMap({x = 32566, y = 32118, z = 07}, 1270, 1274)
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32566, y = 32119, z = 07},{x = 32567, y = 32119, z = 07})
		Game.createItem(1270, 1, {x = 32566, y = 32119, z = 07})
		Game.transformItemOnMap({x = 32566, y = 32118, z = 07}, 1274, 1270)
	end
	return true
end