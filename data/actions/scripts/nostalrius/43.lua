function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 32780, y = 32231, z = 08}, 389)
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32780, y = 32231, z = 08},{x = 32780, y = 32232, z = 08})
		Game.createItem(389, 1, {x = 32780, y = 32231, z = 08})
	end
	return true
end