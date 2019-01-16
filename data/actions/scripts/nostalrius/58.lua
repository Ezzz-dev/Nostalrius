function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 32095, y = 32173, z = 08}, 1271)
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32095, y = 32173, z = 08},{x = 32095, y = 32174, z = 08})
		Game.createItem(1271, 1, {x = 32095, y = 32173, z = 08})
	end

	return true
end