function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
		doRelocate({x = 32623, y = 32189, z = 09},{x = 32623, y = 32190, z = 09}, true)
		doRelocate({x = 32623, y = 32188, z = 09},{x = 32623, y = 32189, z = 09}, true)
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32623, y = 32188, z = 09},{x = 32622, y = 32189, z = 09}, true)
		doRelocate({x = 32623, y = 32189, z = 09},{x = 32623, y = 32188, z = 09}, true)
	end
	return true
end