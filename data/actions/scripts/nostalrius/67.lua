function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
		doRelocate({x = 32225, y = 32276, z = 08},{x = 32225, y = 32276, z = 09})
		Game.transformItemOnMap({x = 32225, y = 32276, z = 08}, 351, 369)
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		Game.transformItemOnMap({x = 32225, y = 32276, z = 08}, 369, 351)
	end
	return true
end